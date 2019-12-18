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

int32_t mz_zip_attrib_posix_to_win32(uint32_t posix_attrib, uint32_t *win32_attrib)
{
    if (win32_attrib == NULL)
        return MZ_PARAM_ERROR;

    *win32_attrib = 0;

    /* S_IWUSR | S_IWGRP | S_IWOTH | S_IXUSR | S_IXGRP | S_IXOTH */
    if ((posix_attrib & 0000333) == 0 && (posix_attrib & 0000444) != 0)
        *win32_attrib |= 0x01;      /* FILE_ATTRIBUTE_READONLY */
    /* S_IFLNK */
    if ((posix_attrib & 0170000) == 0120000)
        *win32_attrib |= 0x400;     /* FILE_ATTRIBUTE_REPARSE_POINT */
    /* S_IFDIR */
    else if ((posix_attrib & 0170000) == 0040000)
        *win32_attrib |= 0x10;      /* FILE_ATTRIBUTE_DIRECTORY */
    /* S_IFREG */
    else
        *win32_attrib |= 0x80;      /* FILE_ATTRIBUTE_NORMAL */

    return MZ_OK;
}