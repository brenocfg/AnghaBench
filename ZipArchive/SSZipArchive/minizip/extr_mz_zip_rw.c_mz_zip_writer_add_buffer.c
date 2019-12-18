#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mz_zip_file ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  MZ_OPEN_MODE_READ ; 
 scalar_t__ MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  mz_stream_mem_create (void**) ; 
 int /*<<< orphan*/  mz_stream_mem_delete (void**) ; 
 scalar_t__ mz_stream_mem_open (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_stream_mem_read ; 
 int /*<<< orphan*/  mz_stream_mem_set_buffer (void*,void*,scalar_t__) ; 
 scalar_t__ mz_zip_writer_add_info (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mz_zip_writer_is_open (void*) ; 

int32_t mz_zip_writer_add_buffer(void *handle, void *buf, int32_t len, mz_zip_file *file_info)
{
    void *mem_stream = NULL;
    int32_t err = MZ_OK;

    if (mz_zip_writer_is_open(handle) != MZ_OK)
        return MZ_PARAM_ERROR;
    if (buf == NULL)
        return MZ_PARAM_ERROR;

    /* Create a memory stream backed by our buffer and add from it */
    mz_stream_mem_create(&mem_stream);
    mz_stream_mem_set_buffer(mem_stream, buf, len);

    err = mz_stream_mem_open(mem_stream, NULL, MZ_OPEN_MODE_READ);
    if (err == MZ_OK)
        err = mz_zip_writer_add_info(handle, mem_stream, mz_stream_mem_read, file_info);

    mz_stream_mem_delete(&mem_stream);
    return err;
}