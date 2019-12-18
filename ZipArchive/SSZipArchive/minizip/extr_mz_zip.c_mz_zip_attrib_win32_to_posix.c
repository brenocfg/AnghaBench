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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 

int32_t mz_zip_attrib_win32_to_posix(uint32_t win32_attrib, uint32_t *posix_attrib)
{
    if (posix_attrib == NULL)
        return MZ_PARAM_ERROR;

    *posix_attrib = 0000444;        /* S_IRUSR | S_IRGRP | S_IROTH */
    /* FILE_ATTRIBUTE_READONLY */
    if ((win32_attrib & 0x01) == 0)
        *posix_attrib |= 0000222;   /* S_IWUSR | S_IWGRP | S_IWOTH */
    /* FILE_ATTRIBUTE_REPARSE_POINT */
    if ((win32_attrib & 0x400) == 0x400)
        *posix_attrib |= 0120000;   /* S_IFLNK */
    /* FILE_ATTRIBUTE_DIRECTORY */
    else if ((win32_attrib & 0x10) == 0x10)
        *posix_attrib |= 0040111;   /* S_IFDIR | S_IXUSR | S_IXGRP | S_IXOTH */
    else
        *posix_attrib |= 0100000;   /* S_IFREG */

    return MZ_OK;
}