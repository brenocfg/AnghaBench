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
typedef  int pid_t ;
typedef  char gchar ;

/* Variables and functions */
 char* APPIMAGEIGNORE ; 
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 char* exclude_file ; 
 int /*<<< orphan*/  execvp (char*,char**) ; 
 int fork () ; 
 char* g_strdup_printf (char*,int) ; 
 char* pathToMksquashfs ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* sqfs_comp ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 

int sfs_mksquashfs(char *source, char *destination, int offset) {
    pid_t pid = fork();
    
    if (pid == -1) {
        // error, failed to fork()
        return(-1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        // we are the child
        gchar* offset_string;
        offset_string = g_strdup_printf("%i", offset);

        char* args[32];
        bool use_xz = strcmp(sqfs_comp, "xz") >= 0;

        int i = 0;
#ifndef AUXILIARY_FILES_DESTINATION
        args[i++] = "mksquashfs";
#else
        args[i++] = pathToMksquashfs;
#endif
        args[i++] = source;
        args[i++] = destination;
        args[i++] = "-offset";
        args[i++] = offset_string;
        args[i++] = "-comp";

        if (use_xz)
            args[i++] = "xz";
        else
            args[i++] = sqfs_comp;

        args[i++] = "-root-owned";
        args[i++] = "-noappend";

        if (use_xz) {
            // https://jonathancarter.org/2015/04/06/squashfs-performance-testing/ says:
            // improved performance by using a 16384 block size with a sacrifice of around 3% more squashfs image space
            args[i++] = "-Xdict-size";
            args[i++] = "100%";
            args[i++] = "-b";
            args[i++] = "16384";
        }

        // check if ignore file exists and use it if possible
        if (access(APPIMAGEIGNORE, F_OK) >= 0) {
            printf("Including %s", APPIMAGEIGNORE);
            args[i++] = "-wildcards";
            args[i++] = "-ef";

            // avoid warning: assignment discards ‘const’ qualifier
            char* buf = strdup(APPIMAGEIGNORE);
            args[i++] = buf;
        }

        // if an exclude file has been passed on the command line, should be used, too
        if (exclude_file != 0 && strlen(exclude_file) > 0) {
            if (access(exclude_file, F_OK) < 0) {
                printf("WARNING: exclude file %s not found!", exclude_file);
                return -1;
            }

            args[i++] = "-wildcards";
            args[i++] = "-ef";
            args[i++] = exclude_file;
        }

        args[i++] = "-mkfs-time";
        args[i++] = "0";

        args[i++] = 0;

        if (verbose) {
            printf("mksquashfs commandline: ");
            for (char** t = args; *t != 0; t++) {
                printf("%s ", *t);
            }
            printf("\n");
        }

#ifndef AUXILIARY_FILES_DESTINATION
        execvp("mksquashfs", args);
#else
        execvp(pathToMksquashfs, args);
#endif

        perror("execlp");   // exec*() returns only on error
        return -1; // exec never returns
    }
    return 0;
}