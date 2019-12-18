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
typedef  long long uint64_t ;
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_OK ; 

int32_t mz_zip_ntfs_to_unix_time(uint64_t ntfs_time, time_t *unix_time)
{
    *unix_time = (time_t)((ntfs_time - 116444736000000000LL) / 10000000);
    return MZ_OK;
}