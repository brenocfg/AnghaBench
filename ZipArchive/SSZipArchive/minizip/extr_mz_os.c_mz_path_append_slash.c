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
typedef  int int32_t ;

/* Variables and functions */
 int MZ_BUF_ERROR ; 
 int MZ_OK ; 
 int /*<<< orphan*/  strlen (char*) ; 

int32_t mz_path_append_slash(char *path, int32_t max_path, char slash)
{
    int32_t path_len = (int32_t)strlen(path);
    if ((path_len + 2) >= max_path)
        return MZ_BUF_ERROR;
    if (path[path_len - 1] != '\\' && path[path_len - 1] != '/')
    {
        path[path_len] = slash;
        path[path_len + 1] = 0;
    }
    return MZ_OK;
}