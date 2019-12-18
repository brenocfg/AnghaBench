#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mz_zip_file ;
struct TYPE_2__ {int open_mode; int /*<<< orphan*/  file_info; int /*<<< orphan*/  entry_scanned; } ;
typedef  TYPE_1__ mz_zip ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_OK ; 
 int MZ_OPEN_MODE_WRITE ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 

int32_t mz_zip_entry_get_info(void *handle, mz_zip_file **file_info)
{
    mz_zip *zip = (mz_zip *)handle;

    if (zip == NULL)
        return MZ_PARAM_ERROR;

    if ((zip->open_mode & MZ_OPEN_MODE_WRITE) == 0)
    {
        if (!zip->entry_scanned)
            return MZ_PARAM_ERROR;
    }

    *file_info = &zip->file_info;
    return MZ_OK;
}