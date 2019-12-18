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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  fullpath ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  S_IRWXU ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  mkdir (char*,int /*<<< orphan*/ ) ; 
 size_t readlink (char const*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

void
portable_option(const char *arg, const char *appimage_path, const char *name)
{
    char option[32];
    sprintf(option, "appimage-portable-%s", name);

    if (arg && strcmp(arg, option)==0) {
        char portable_dir[PATH_MAX];
        char fullpath[PATH_MAX];

        ssize_t length = readlink(appimage_path, fullpath, sizeof(fullpath));
        if (length < 0) {
            fprintf(stderr, "Error getting realpath for %s\n", appimage_path);
            exit(EXIT_FAILURE);
        }
        fullpath[length] = '\0';

        sprintf(portable_dir, "%s.%s", fullpath, name);
        if (!mkdir(portable_dir, S_IRWXU))
            fprintf(stderr, "Portable %s directory created at %s\n", name, portable_dir);
        else
            fprintf(stderr, "Error creating portable %s directory at %s: %s\n", name, portable_dir, strerror(errno));

        exit(0);
    }
}