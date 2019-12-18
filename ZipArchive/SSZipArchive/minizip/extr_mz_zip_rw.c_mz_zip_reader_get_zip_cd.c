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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  cd_zipped; } ;
typedef  TYPE_1__ mz_zip_reader ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 

int32_t mz_zip_reader_get_zip_cd(void *handle, uint8_t *zip_cd)
{
    mz_zip_reader *reader = (mz_zip_reader *)handle;
    if (zip_cd == NULL)
        return MZ_PARAM_ERROR;
    *zip_cd = reader->cd_zipped;
    return MZ_OK;
}