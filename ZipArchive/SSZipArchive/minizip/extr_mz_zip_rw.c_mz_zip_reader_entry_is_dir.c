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
struct TYPE_2__ {int /*<<< orphan*/  zip_handle; } ;
typedef  TYPE_1__ mz_zip_reader ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  mz_zip_entry_is_dir (int /*<<< orphan*/ ) ; 
 scalar_t__ mz_zip_reader_is_open (void*) ; 

int32_t mz_zip_reader_entry_is_dir(void *handle)
{
    mz_zip_reader *reader = (mz_zip_reader *)handle;
    if (mz_zip_reader_is_open(handle) != MZ_OK)
        return MZ_PARAM_ERROR;
    return mz_zip_entry_is_dir(reader->zip_handle);
}