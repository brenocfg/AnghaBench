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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int ENOENT ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int rmdir (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strerror (int) ; 
 int strlen (char*) ; 
 int unlink (char*) ; 

__attribute__((used)) static void
rmtree(char *path)
{
    int r = unlink(path);
    if (r == 0 || errno == ENOENT) {
        return; /* success */
    }
    int unlinkerr = errno;

    DIR *d = opendir(path);
    if (!d) {
        if (errno == ENOTDIR) {
            fprintf(stderr, "ct: unlink: %s\n", strerror(unlinkerr));
        } else {
            perror("ct: opendir");
        }
        fprintf(stderr, "ct: path %s\n", path);
        return;
    }
    struct dirent *ent;
    while ((ent = readdir(d))) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }
        int n = strlen(path) + 1 + strlen(ent->d_name);
        char s[n+1];
        sprintf(s, "%s/%s", path, ent->d_name);
        rmtree(s);
    }
    closedir(d);
    r = rmdir(path);
    if (r == -1) {
        perror("ct: rmdir");
        fprintf(stderr, "ct: path %s\n", path);
    }
}