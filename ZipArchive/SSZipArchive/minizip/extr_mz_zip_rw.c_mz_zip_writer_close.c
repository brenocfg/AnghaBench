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
struct TYPE_3__ {int /*<<< orphan*/ * mem_stream; int /*<<< orphan*/ * file_stream; int /*<<< orphan*/ * buffered_stream; int /*<<< orphan*/ * split_stream; int /*<<< orphan*/ * zip_handle; scalar_t__ zip_cd; scalar_t__ comment; } ;
typedef  TYPE_1__ mz_zip_writer ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_VERSION_MADEBY ; 
 int /*<<< orphan*/  mz_stream_buffered_delete (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_stream_mem_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_stream_mem_delete (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_stream_os_delete (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_stream_split_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_stream_split_delete (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_zip_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_zip_delete (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_zip_set_comment (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mz_zip_set_version_madeby (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_zip_writer_zip_cd (TYPE_1__*) ; 

int32_t mz_zip_writer_close(void *handle)
{
    mz_zip_writer *writer = (mz_zip_writer *)handle;
    int32_t err = MZ_OK;


    if (writer->zip_handle != NULL)
    {
        mz_zip_set_version_madeby(writer->zip_handle, MZ_VERSION_MADEBY);
        if (writer->comment)
            mz_zip_set_comment(writer->zip_handle, writer->comment);
        if (writer->zip_cd)
            mz_zip_writer_zip_cd(writer);

        err = mz_zip_close(writer->zip_handle);
        mz_zip_delete(&writer->zip_handle);
    }

    if (writer->split_stream != NULL)
    {
        mz_stream_split_close(writer->split_stream);
        mz_stream_split_delete(&writer->split_stream);
    }

    if (writer->buffered_stream != NULL)
        mz_stream_buffered_delete(&writer->buffered_stream);

    if (writer->file_stream != NULL)
        mz_stream_os_delete(&writer->file_stream);

    if (writer->mem_stream != NULL)
    {
        mz_stream_mem_close(writer->mem_stream);
        mz_stream_mem_delete(&writer->mem_stream);
    }

    return err;
}