#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* filename; int /*<<< orphan*/  version_madeby; int /*<<< orphan*/  external_fa; } ;
struct TYPE_4__ {scalar_t__ entry_scanned; TYPE_1__ file_info; } ;
typedef  TYPE_2__ mz_zip ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_EXIST_ERROR ; 
 scalar_t__ MZ_OK ; 
 scalar_t__ MZ_PARAM_ERROR ; 
 scalar_t__ mz_zip_attrib_is_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

int32_t mz_zip_entry_is_dir(void *handle)
{
    mz_zip *zip = (mz_zip *)handle;
    int32_t filename_length = 0;

    if (zip == NULL)
        return MZ_PARAM_ERROR;
    if (zip->entry_scanned == 0)
        return MZ_PARAM_ERROR;
    if (mz_zip_attrib_is_dir(zip->file_info.external_fa, zip->file_info.version_madeby) == MZ_OK)
        return MZ_OK;

    filename_length = (int32_t)strlen(zip->file_info.filename);
    if (filename_length > 0)
    {
        if ((zip->file_info.filename[filename_length - 1] == '/') ||
            (zip->file_info.filename[filename_length - 1] == '\\'))
            return MZ_OK;
    }
    return MZ_EXIST_ERROR;
}