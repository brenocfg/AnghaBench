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
 int /*<<< orphan*/  MZ_EXIST_ERROR ; 
 int /*<<< orphan*/  MZ_OK ; 
 int rename (char const*,char const*) ; 

int32_t mz_os_rename(const char *source_path, const char *target_path)
{
    if (rename(source_path, target_path) == -1)
        return MZ_EXIST_ERROR;

    return MZ_OK;
}