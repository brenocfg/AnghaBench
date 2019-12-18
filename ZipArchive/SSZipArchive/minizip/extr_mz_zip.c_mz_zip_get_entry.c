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
struct TYPE_2__ {int /*<<< orphan*/  cd_current_pos; } ;
typedef  TYPE_1__ mz_zip ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 

int64_t mz_zip_get_entry(void *handle)
{
    mz_zip *zip = (mz_zip *)handle;

    if (zip == NULL)
        return MZ_PARAM_ERROR;

    return zip->cd_current_pos;
}