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
struct TYPE_2__ {scalar_t__ cd_start_pos; scalar_t__ cd_size; scalar_t__ cd_current_pos; } ;
typedef  TYPE_1__ mz_zip ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  mz_zip_goto_next_entry_int (void*) ; 

int32_t mz_zip_goto_entry(void *handle, int64_t cd_pos)
{
    mz_zip *zip = (mz_zip *)handle;

    if (zip == NULL)
        return MZ_PARAM_ERROR;

    if (cd_pos < zip->cd_start_pos || cd_pos > zip->cd_start_pos + zip->cd_size)
        return MZ_PARAM_ERROR;

    zip->cd_current_pos = cd_pos;

    return mz_zip_goto_next_entry_int(handle);
}