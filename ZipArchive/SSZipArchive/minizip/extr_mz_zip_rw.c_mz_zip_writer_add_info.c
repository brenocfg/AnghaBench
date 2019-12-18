#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  version_madeby; int /*<<< orphan*/  external_fa; } ;
struct TYPE_4__ {TYPE_1__ file_info; } ;
typedef  TYPE_2__ mz_zip_writer ;
typedef  int /*<<< orphan*/  mz_zip_file ;
typedef  int /*<<< orphan*/  mz_stream_read_cb ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 scalar_t__ MZ_PARAM_ERROR ; 
 scalar_t__ mz_zip_attrib_is_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mz_zip_writer_add (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ mz_zip_writer_entry_close (void*) ; 
 scalar_t__ mz_zip_writer_entry_open (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ mz_zip_writer_is_open (void*) ; 

int32_t mz_zip_writer_add_info(void *handle, void *stream, mz_stream_read_cb read_cb, mz_zip_file *file_info)
{
    mz_zip_writer *writer = (mz_zip_writer *)handle;
    int32_t err = MZ_OK;


    if (mz_zip_writer_is_open(handle) != MZ_OK)
        return MZ_PARAM_ERROR;
    if (file_info == NULL)
        return MZ_PARAM_ERROR;

    /* Add to zip */
    err = mz_zip_writer_entry_open(handle, file_info);
    if (err != MZ_OK)
        return err;

    if (stream != NULL)
    {
        if (mz_zip_attrib_is_dir(writer->file_info.external_fa, writer->file_info.version_madeby) != MZ_OK)
        {
            err = mz_zip_writer_add(handle, stream, read_cb);
            if (err != MZ_OK)
                return err;
        }
    }

    err = mz_zip_writer_entry_close(handle);

    return err;
}