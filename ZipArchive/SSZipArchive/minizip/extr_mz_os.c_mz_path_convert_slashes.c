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
 int MZ_OK ; 
 scalar_t__ strlen (char*) ; 

int32_t mz_path_convert_slashes(char *path, char slash)
{
    int32_t i = 0;

    for (i = 0; i < (int32_t)strlen(path); i += 1)
    {
        if (path[i] == '\\' || path[i] == '/')
            path[i] = slash;
    }
    return MZ_OK;
}