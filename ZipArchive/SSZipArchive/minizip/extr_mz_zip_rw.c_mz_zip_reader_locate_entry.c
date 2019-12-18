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
struct TYPE_2__ {int /*<<< orphan*/ * file_info; int /*<<< orphan*/  zip_handle; } ;
typedef  TYPE_1__ mz_zip_reader ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 scalar_t__ mz_zip_entry_get_info (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ mz_zip_entry_is_open (int /*<<< orphan*/ ) ; 
 scalar_t__ mz_zip_locate_entry (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_zip_reader_entry_close (void*) ; 

int32_t mz_zip_reader_locate_entry(void *handle, const char *filename, uint8_t ignore_case)
{
    mz_zip_reader *reader = (mz_zip_reader *)handle;
    int32_t err = MZ_OK;

    if (mz_zip_entry_is_open(reader->zip_handle) == MZ_OK)
        mz_zip_reader_entry_close(handle);

    err = mz_zip_locate_entry(reader->zip_handle, filename, ignore_case);

    reader->file_info = NULL;
    if (err == MZ_OK)
        err = mz_zip_entry_get_info(reader->zip_handle, &reader->file_info);

    return err;
}