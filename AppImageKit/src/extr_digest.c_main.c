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
struct stat {int st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  appimage_get_elf_section_offset_and_length (char*,char*,unsigned long*,unsigned long*) ; 
 unsigned long atoi (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* segment_name ; 
 int sha256_file (char*,char*,unsigned long,unsigned long) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc,char **argv)
{
    int res = 0;

    if(argc < 2){
        fprintf(stderr, "Usage: %s file offset length\n", argv[0]);
        fprintf(stderr, "If no offset and length are provided, the ELF section '%s' is skipped\n\n", segment_name);
        fprintf(stderr, "Calculate a sha256 of a file except a skipped area from offset to offset+length bytes\n");
        fprintf(stderr, "which is replaced with 0x00 during checksum calculation.\n");
        fprintf(stderr, "This is useful when a signature is placed in the skipped area.\n");
        exit(1);
    }

    unsigned long skip_offset = 0;
    unsigned long skip_length = 0;
    char *filename = argv[1];
        
    struct stat st;
    if (stat(filename, &st) < 0) {
        fprintf(stderr, "not existing file: %s\n", filename);
        exit(1);
    }

    if(argc < 4){
        appimage_get_elf_section_offset_and_length(filename, ".sha256_sig", &skip_offset, &skip_length);
        if(skip_length > 0)
            fprintf(stderr, "Skipping ELF section %s with offset %lu, length %lu\n", segment_name, skip_offset, skip_length);
    } else if(argc == 4) {
        skip_offset = atoi(argv[2]);
        skip_length = atoi(argv[3]);
    } else {
        exit(1);
    }

    int size = st.st_size;
    if(size < skip_offset+skip_length){
        fprintf(stderr, "offset+length cannot be less than the file size\n");
        exit(1);
    }

    static char buffer[65];
    res = sha256_file(filename, buffer, skip_offset, skip_length);
    printf("%s\n", buffer);
    return res;
}