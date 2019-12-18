#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * file_info; int /*<<< orphan*/  zip_handle; int /*<<< orphan*/ * pattern; } ;
typedef  TYPE_1__ mz_zip_reader ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 scalar_t__ MZ_PARAM_ERROR ; 
 scalar_t__ mz_zip_entry_get_info (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ mz_zip_entry_is_open (int /*<<< orphan*/ ) ; 
 scalar_t__ mz_zip_goto_first_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ mz_zip_locate_first_entry (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_zip_reader_entry_close (void*) ; 
 scalar_t__ mz_zip_reader_is_open (void*) ; 
 int /*<<< orphan*/  mz_zip_reader_locate_entry_cb ; 

int32_t mz_zip_reader_goto_first_entry(void *handle)
{
    mz_zip_reader *reader = (mz_zip_reader *)handle;
    int32_t err = MZ_OK;

    if (mz_zip_reader_is_open(handle) != MZ_OK)
        return MZ_PARAM_ERROR;

    if (mz_zip_entry_is_open(reader->zip_handle) == MZ_OK)
        mz_zip_reader_entry_close(handle);

    if (reader->pattern == NULL)
        err = mz_zip_goto_first_entry(reader->zip_handle);
    else
        err = mz_zip_locate_first_entry(reader->zip_handle, reader, mz_zip_reader_locate_entry_cb);

    reader->file_info = NULL;
    if (err == MZ_OK)
        err = mz_zip_entry_get_info(reader->zip_handle, &reader->file_info);

    return err;
}