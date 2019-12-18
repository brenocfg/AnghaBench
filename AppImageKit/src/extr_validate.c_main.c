#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
struct stat {int st_size; } ;
typedef  char gchar ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  G_FILE_TEST_IS_REGULAR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int WEXITSTATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appimage_get_elf_section_offset_and_length (char*,char*,unsigned long*,unsigned long*) ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fread (int*,unsigned long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_file_test (char*,int /*<<< orphan*/ ) ; 
 char* g_find_program_in_path (char*) ; 
 char* g_strconcat (char*,char*,int /*<<< orphan*/ *) ; 
 int* malloc (unsigned long) ; 
 int /*<<< orphan*/  pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* segment_name ; 
 int /*<<< orphan*/  sha256_file (char*,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  unlink (char*) ; 

int main(int argc,char **argv)	{
    if(argc < 2){
        fprintf(stderr, "Usage: %s Signed.AppImage\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1]; 

    unsigned long skip_offset = 0;
    unsigned long skip_length = 0;
  
    if (!appimage_get_elf_section_offset_and_length(filename, ".sha256_sig", &skip_offset, &skip_length)) {
        fprintf(stderr, "Failed to read .sha256_sig section");
        exit(1);
    }

    if(skip_length > 0) {
        fprintf(stderr, "Skipping ELF section %s with offset %lu, length %lu\n", segment_name, skip_offset, skip_length);
    } else {
        fprintf(stderr, "ELF section %s not found, is the file signed?\n", segment_name);
        exit(1);
    }
    
    char *digestfile;
    digestfile = g_strconcat("/tmp/", basename(g_strconcat(filename, ".digest", NULL)), NULL);
    char *signaturefile;
    signaturefile = g_strconcat("/tmp/", basename(g_strconcat(filename, ".sig", NULL)), NULL);

    uint8_t *data = malloc(skip_length);
    unsigned long k;
    FILE* fd = fopen(filename, "r");
    fseek(fd, skip_offset, SEEK_SET);
    fread(data, skip_length, sizeof(uint8_t), fd);
    fclose(fd);
    FILE *fpdst2 = fopen(signaturefile, "w");
    if (fpdst2 == NULL) {
        fprintf(stderr, "Not able to open the signature file for writing, aborting");
        exit(1);
    }
    for (k = 0; k < skip_length; k++) {
        fprintf(fpdst2, "%c", data[k]);
    }   
    fclose(fpdst2);
    free(data);
    
    struct stat st;
    stat(filename, &st);
    int size = st.st_size;
    if(size < skip_offset+skip_length){
        fprintf(stderr, "offset+length cannot be less than the file size\n");
        exit(1);
    }

    static char buffer[65];
    sha256_file(filename, buffer, skip_offset, skip_length);
    printf("%s\n", buffer);
    

    FILE *f = fopen(digestfile, "w");
    if (f == NULL){
        printf("Error opening digestfile\n");
        exit(1);
    }
    fprintf(f, "%s", buffer);
    fclose(f);
    if (! g_file_test(digestfile, G_FILE_TEST_IS_REGULAR)) {
        printf("Error writing digestfile\n");
        exit(1);        
    }
    
    char command[1024];
    gchar *gpg2_path = g_find_program_in_path ("gpg2");
    sprintf (command, "%s --verify %s %s", gpg2_path, signaturefile, digestfile);
    fprintf (stderr, "%s\n", command);
    FILE *fp = popen(command, "r");
    if (fp == NULL)
        fprintf(stderr, "gpg2 command did not succeed");
    int exitcode = WEXITSTATUS(pclose(fp));
    unlink(digestfile);
    unlink(signaturefile);
    return exitcode;
}