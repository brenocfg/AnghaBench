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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  disk_number_with_cd; } ;
typedef  TYPE_1__ mz_zip ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 

int32_t mz_zip_get_disk_number_with_cd(void *handle, uint32_t *disk_number_with_cd)
{
    mz_zip *zip = (mz_zip *)handle;
    if (zip == NULL || disk_number_with_cd == NULL)
        return MZ_PARAM_ERROR;
    *disk_number_with_cd = zip->disk_number_with_cd;
    return MZ_OK;
}