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
struct TYPE_2__ {int /*<<< orphan*/ * mem_stream; int /*<<< orphan*/ * file_stream; int /*<<< orphan*/ * buffered_stream; int /*<<< orphan*/ * split_stream; int /*<<< orphan*/ * zip_handle; } ;
typedef  TYPE_1__ mz_zip_reader ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  mz_stream_buffered_delete (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_stream_mem_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_stream_mem_delete (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_stream_os_delete (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_stream_split_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_stream_split_delete (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_zip_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_zip_delete (int /*<<< orphan*/ **) ; 

int32_t mz_zip_reader_close(void *handle)
{
    mz_zip_reader *reader = (mz_zip_reader *)handle;
    int32_t err = MZ_OK;

    if (reader->zip_handle != NULL)
    {
        err = mz_zip_close(reader->zip_handle);
        mz_zip_delete(&reader->zip_handle);
    }

    if (reader->split_stream != NULL)
    {
        mz_stream_split_close(reader->split_stream);
        mz_stream_split_delete(&reader->split_stream);
    }

    if (reader->buffered_stream != NULL)
        mz_stream_buffered_delete(&reader->buffered_stream);

    if (reader->file_stream != NULL)
        mz_stream_os_delete(&reader->file_stream);

    if (reader->mem_stream != NULL)
    {
        mz_stream_mem_close(reader->mem_stream);
        mz_stream_mem_delete(&reader->mem_stream);
    }

    return err;
}