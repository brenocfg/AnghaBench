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
struct TYPE_2__ {void* zip_handle; } ;
typedef  TYPE_1__ mz_zip_writer ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_EXIST_ERROR ; 
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 

int32_t mz_zip_writer_get_zip_handle(void *handle, void **zip_handle)
{
    mz_zip_writer *writer = (mz_zip_writer *)handle;
    if (zip_handle == NULL)
        return MZ_PARAM_ERROR;
    *zip_handle = writer->zip_handle;
    if (*zip_handle == NULL)
        return MZ_EXIST_ERROR;
    return MZ_OK;
}