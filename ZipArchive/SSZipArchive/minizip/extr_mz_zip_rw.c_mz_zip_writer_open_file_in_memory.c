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
struct TYPE_2__ {int /*<<< orphan*/  mem_stream; } ;
typedef  TYPE_1__ mz_zip_writer ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_MEM_ERROR ; 
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  MZ_OPEN_MODE_CREATE ; 
 int /*<<< orphan*/  MZ_OPEN_MODE_READ ; 
 int /*<<< orphan*/  MZ_SEEK_END ; 
 int /*<<< orphan*/  MZ_SEEK_SET ; 
 scalar_t__ UINT32_MAX ; 
 scalar_t__ mz_stream_copy (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  mz_stream_mem_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_stream_mem_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_stream_mem_set_grow_size (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mz_stream_os_close (void*) ; 
 int /*<<< orphan*/  mz_stream_os_create (void**) ; 
 int /*<<< orphan*/  mz_stream_os_delete (void**) ; 
 scalar_t__ mz_stream_os_open (void*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_stream_os_seek (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mz_stream_os_tell (void*) ; 
 int /*<<< orphan*/  mz_zip_writer_close (void*) ; 
 scalar_t__ mz_zip_writer_open (void*,int /*<<< orphan*/ ) ; 

int32_t mz_zip_writer_open_file_in_memory(void *handle, const char *path)
{
    mz_zip_writer *writer = (mz_zip_writer *)handle;
    void *file_stream = NULL;
    int64_t file_size = 0;
    int32_t err = 0;


    mz_zip_writer_close(handle);

    mz_stream_os_create(&file_stream);

    err = mz_stream_os_open(file_stream, path, MZ_OPEN_MODE_READ);

    if (err != MZ_OK)
    {
        mz_stream_os_delete(&file_stream);
        mz_zip_writer_close(handle);
        return err;
    }

    mz_stream_os_seek(file_stream, 0, MZ_SEEK_END);
    file_size = mz_stream_os_tell(file_stream);
    mz_stream_os_seek(file_stream, 0, MZ_SEEK_SET);

    if ((file_size <= 0) || (file_size > UINT32_MAX))
    {
        /* Memory size is too large or too small */

        mz_stream_os_close(file_stream);
        mz_stream_os_delete(&file_stream);
        mz_zip_writer_close(handle);
        return MZ_MEM_ERROR;
    }

    mz_stream_mem_create(&writer->mem_stream);
    mz_stream_mem_set_grow_size(writer->mem_stream, (int32_t)file_size);
    mz_stream_mem_open(writer->mem_stream, NULL, MZ_OPEN_MODE_CREATE);

    err = mz_stream_copy(writer->mem_stream, file_stream, (int32_t)file_size);

    mz_stream_os_close(file_stream);
    mz_stream_os_delete(&file_stream);

    if (err == MZ_OK)
        err = mz_zip_writer_open(handle, writer->mem_stream);
    if (err != MZ_OK)
        mz_zip_writer_close(handle);

    return err;
}