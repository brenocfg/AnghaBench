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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  extrafield_size; int /*<<< orphan*/  const* extrafield; } ;
struct TYPE_4__ {TYPE_1__ file_info; } ;
typedef  TYPE_2__ mz_zip ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 scalar_t__ MZ_PARAM_ERROR ; 
 scalar_t__ mz_zip_entry_is_open (void*) ; 

int32_t mz_zip_entry_set_extrafield(void *handle, const uint8_t *extrafield, uint16_t extrafield_size)
{
    mz_zip *zip = (mz_zip *)handle;

    if (zip == NULL || mz_zip_entry_is_open(handle) != MZ_OK)
        return MZ_PARAM_ERROR;

    zip->file_info.extrafield = extrafield;
    zip->file_info.extrafield_size = extrafield_size;
    return MZ_OK;
}