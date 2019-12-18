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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {scalar_t__ progress_cb_interval_ms; int /*<<< orphan*/  file_info; int /*<<< orphan*/  progress_userdata; int /*<<< orphan*/  (* progress_cb ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ;} ;
typedef  TYPE_1__ mz_zip_writer ;
typedef  int /*<<< orphan*/  mz_stream_read_cb ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_END_OF_STREAM ; 
 scalar_t__ MZ_OK ; 
 scalar_t__ mz_os_ms_time () ; 
 scalar_t__ mz_zip_writer_add_process (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

int32_t mz_zip_writer_add(void *handle, void *stream, mz_stream_read_cb read_cb)
{
    mz_zip_writer *writer = (mz_zip_writer *)handle;
    uint64_t current_time = 0;
    uint64_t update_time = 0;
    int64_t current_pos = 0;
    int64_t update_pos = 0;
    int32_t err = MZ_OK;
    int32_t written = 0;

    /* Update the progress at the beginning */
    if (writer->progress_cb != NULL)
        writer->progress_cb(handle, writer->progress_userdata, &writer->file_info, current_pos);

    /* Write data to stream until done */
    while (err == MZ_OK)
    {
        written = mz_zip_writer_add_process(handle, stream, read_cb);
        if (written == MZ_END_OF_STREAM)
            break;
        if (written > 0)
            current_pos += written;
        if (written < 0)
            err = written;

        /* Update progress if enough time have passed */
        current_time = mz_os_ms_time();
        if ((current_time - update_time) > writer->progress_cb_interval_ms)
        {
            if (writer->progress_cb != NULL)
                writer->progress_cb(handle, writer->progress_userdata, &writer->file_info, current_pos);

            update_pos = current_pos;
            update_time = current_time;
        }
    }

    /* Update the progress at the end */
    if (writer->progress_cb != NULL && update_pos != current_pos)
        writer->progress_cb(handle, writer->progress_userdata, &writer->file_info, current_pos);

    return err;
}