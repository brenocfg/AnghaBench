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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 
 int strlen (char*) ; 

int32_t mz_path_remove_filename(char *path)
{
    char *path_ptr = NULL;

    if (path == NULL)
        return MZ_PARAM_ERROR;

    path_ptr = path + strlen(path) - 1;

    while (path_ptr > path)
    {
        if ((*path_ptr == '/') || (*path_ptr == '\\'))
        {
            *path_ptr = 0;
            break;
        }

        path_ptr -= 1;
    }

    if (path_ptr == path)
        *path_ptr = 0;

    return MZ_OK;
}