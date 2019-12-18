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
struct arguments {char* dumpfile; char** args; scalar_t__ verbose; scalar_t__ list; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int BrInitError ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  argp ; 
 int /*<<< orphan*/  argp_parse (int /*<<< orphan*/ *,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arguments*) ; 
 char* basename (char*) ; 
 char* br_find_exe_dir (int /*<<< orphan*/ *) ; 
 scalar_t__ br_init (int*) ; 
 char* br_strcat (char*,char*) ; 
 scalar_t__ chmod (char*,int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ftruncate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ is_directory (char*) ; 
 scalar_t__ is_regular_file (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  realpath (char*,char*) ; 
 char* runtime ; 
 int runtime_len ; 
 int /*<<< orphan*/  sfs_ls (char*) ; 
 int sfs_mksquashfs (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ unlink (char*) ; 

int main (int argc, char **argv)
{

  /* Initialize binreloc so that we always know where we live */
  BrInitError error;
  if (br_init (&error) == 0) {
    printf ("Warning: binreloc failed to initialize (error code %d)\n", error);
  }
  printf ("This tool is located at %s\n", br_find_exe_dir(NULL));    
    
  struct arguments arguments;

  /* Set argument defaults */
  arguments.list = 0;
  arguments.verbose = 0;
  arguments.dumpfile = NULL;
  
  /* Where the magic happens */
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  /* If in list mode */
  if (arguments.list){
    sfs_ls(arguments.args[0]);
    exit(0);
  }
    
  /* If in dumpfile mode */
  if (arguments.dumpfile){
    fprintf (stdout, "%s from the AppImage %s should be dumped to stdout\n", arguments.dumpfile, arguments.args[0]);
    die("To be implemented");
  }
  
  /* Print argument values */
  if (arguments.verbose)
      fprintf (stdout, "Original SOURCE = %s\nOriginal DESTINATION = %s\n",
        arguments.args[0],
        arguments.args[1]);

  /* If the first argument is a directory, then we assume that we should package it */
  if(is_directory(arguments.args[0])){
      char *destination;
      char source[PATH_MAX];
      realpath(arguments.args[0], source);
      if (arguments.args[1]) {
          destination = arguments.args[1];
      } else {
          /* No destination has been specified, to let's construct one
           * TODO: Find out the architecture and use a $VERSION that might be around in the env */
          destination = basename(br_strcat(source, ".AppImage"));
          fprintf (stdout, "DESTINATION not specified, so assuming %s\n", destination);
      }
      fprintf (stdout, "%s should be packaged as %s\n", arguments.args[0], destination);

      /* mksquashfs can currently not start writing at an offset,
       * so we need a tempfile. https://github.com/plougher/squashfs-tools/pull/13
       * should hopefully change that. */
      char *tempfile;
      fprintf (stderr, "Generating squashfs...\n");
      tempfile = br_strcat(destination, ".temp");
      int result = sfs_mksquashfs(source, tempfile);
      if(result != 0)
          die("sfs_mksquashfs error");

      fprintf (stderr, "Generating AppImage...\n");
      FILE *fpsrc = fopen(tempfile, "rb");
      if (fpsrc == NULL) {
         die("Not able to open the tempfile for reading, aborting");
      }
      FILE *fpdst = fopen(destination, "w");
      if (fpdst == NULL) {
         die("Not able to open the destination file for writing, aborting");
      }

      /* runtime is embedded into this executable
       * http://stupefydeveloper.blogspot.de/2008/08/cc-embed-binary-data-into-elf.html */
      int size = runtime_len;
      char *data = runtime;
      if (arguments.verbose)
          printf("Size of the embedded runtime: %d bytes\n", size);
      /* Where to store updateinformation. Fixed offset preferred for easy manipulation 
       * after the fact. Proposal: 4 KB at the end of the 128 KB padding. 
       * Hence, offset 126976, max. 4096 bytes long. 
       * Possibly we might want to store additional information in the future.
       * Assuming 4 blocks of 4096 bytes each.
       */
      if(size > 128*1024-4*4096-2){
          die("Size of the embedded runtime is too large, aborting");
      }
      // printf("%s", data);
      fwrite(data, size, 1, fpdst);

      if(ftruncate(fileno(fpdst), 128*1024) != 0) {
          die("Not able to write padding to destination file, aborting");
      }
      
      fseek (fpdst, 0, SEEK_END);
      char byte;

      while (!feof(fpsrc))
      {
          fread(&byte, sizeof(char), 1, fpsrc);
          fwrite(&byte, sizeof(char), 1, fpdst);
      }
      
      fclose(fpsrc);
      fclose(fpdst);

      fprintf (stderr, "Marking the AppImage as executable...\n");
      if (chmod (destination, 0755) < 0) {
          printf("Could not set executable bit, aborting\n");
          exit(1);
      }
      if(unlink(tempfile) != 0) {
          die("Could not delete the tempfile, aborting");
      }
      fprintf (stderr, "Success\n");
}

  /* If the first argument is a regular file, then we assume that we should unpack it */
  if(is_regular_file(arguments.args[0])){
      fprintf (stdout, "%s is a file, assuming it is an AppImage and should be unpacked\n", arguments.args[0]);
      die("To be implemented");
  }

  return 0;
}