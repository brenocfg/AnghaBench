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
struct TYPE_2__ {int /*<<< orphan*/  cd_start_pos; void* cd_stream; } ;
typedef  TYPE_1__ mz_zip ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 

int32_t mz_zip_set_cd_stream(void *handle, int64_t cd_start_pos, void *cd_stream)
{
    mz_zip *zip = (mz_zip *)handle;
    if (zip == NULL || cd_stream == NULL)
        return MZ_PARAM_ERROR;
    zip->cd_stream = cd_stream;
    zip->cd_start_pos = cd_start_pos;
    return MZ_OK;
}