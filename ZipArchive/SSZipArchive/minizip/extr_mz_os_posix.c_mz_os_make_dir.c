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
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 scalar_t__ MZ_INTERNAL_ERROR ; 
 scalar_t__ MZ_OK ; 
 scalar_t__ errno ; 
 scalar_t__ mkdir (char const*,int) ; 

int32_t mz_os_make_dir(const char *path)
{
    int32_t err = 0;

    err = mkdir(path, 0755);

    if (err != 0 && errno != EEXIST)
        return MZ_INTERNAL_ERROR;

    return MZ_OK;
}