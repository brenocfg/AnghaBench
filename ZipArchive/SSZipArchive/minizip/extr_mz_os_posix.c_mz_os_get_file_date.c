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
typedef  scalar_t__ time_t ;
struct stat {scalar_t__ st_atime; scalar_t__ st_mtime; } ;
typedef  int /*<<< orphan*/  path_stat ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_INTERNAL_ERROR ; 
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mz_path_remove_slash (char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

int32_t mz_os_get_file_date(const char *path, time_t *modified_date, time_t *accessed_date, time_t *creation_date)
{
    struct stat path_stat;
    char *name = NULL;
    size_t len = 0;
    int32_t err = MZ_INTERNAL_ERROR;

    memset(&path_stat, 0, sizeof(path_stat));

    if (strcmp(path, "-") != 0)
    {
        /* Not all systems allow stat'ing a file with / appended */
        len = strlen(path);
        name = (char *)malloc(len + 1);
        strncpy(name, path, len + 1);
        mz_path_remove_slash(name);

        if (stat(name, &path_stat) == 0)
        {
            if (modified_date != NULL)
                *modified_date = path_stat.st_mtime;
            if (accessed_date != NULL)
                *accessed_date = path_stat.st_atime;
            /* Creation date not supported */
            if (creation_date != NULL)
                *creation_date = 0;

            err = MZ_OK;
        }

        free(name);
    }

    return err;
}