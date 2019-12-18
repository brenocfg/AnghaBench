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
typedef  scalar_t__ (* mz_zip_locate_entry_cb ) (void*,void*,int /*<<< orphan*/ *) ;
struct TYPE_2__ {int /*<<< orphan*/  file_info; } ;
typedef  TYPE_1__ mz_zip ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 scalar_t__ mz_zip_goto_next_entry (void*) ; 

int32_t mz_zip_locate_next_entry(void *handle, void *userdata, mz_zip_locate_entry_cb cb)
{
    mz_zip *zip = (mz_zip *)handle;
    int32_t err = MZ_OK;
    int32_t result = 0;

    /* Search next entries looking for match */
    err = mz_zip_goto_next_entry(handle);
    while (err == MZ_OK)
    {
        result = cb(handle, userdata, &zip->file_info);
        if (result == 0)
            return MZ_OK;

        err = mz_zip_goto_next_entry(handle);
    }

    return err;
}