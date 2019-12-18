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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_EXIST_ERROR ; 
 int /*<<< orphan*/  MZ_HOST_SYSTEM (scalar_t__) ; 
 int /*<<< orphan*/  MZ_HOST_SYSTEM_UNIX ; 
 scalar_t__ MZ_OK ; 
 scalar_t__ mz_zip_attrib_convert (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

int32_t mz_zip_attrib_is_symlink(uint32_t attrib, int32_t version_madeby)
{
    uint32_t posix_attrib = 0;
    uint8_t system = MZ_HOST_SYSTEM(version_madeby);
    int32_t err = MZ_OK;

    err = mz_zip_attrib_convert(system, attrib, MZ_HOST_SYSTEM_UNIX, &posix_attrib);
    if (err == MZ_OK)
    {
        if ((posix_attrib & 0170000) == 0120000) /* S_ISLNK */
            return MZ_OK;
    }

    return MZ_EXIST_ERROR;
}