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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  mem_stream; } ;
typedef  TYPE_1__ mz_zip_reader ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  MZ_OPEN_MODE_CREATE ; 
 int /*<<< orphan*/  MZ_OPEN_MODE_READ ; 
 int /*<<< orphan*/  MZ_SEEK_SET ; 
 int /*<<< orphan*/  mz_stream_mem_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_stream_mem_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_stream_mem_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_stream_mem_set_buffer (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  mz_stream_mem_set_grow_size (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mz_stream_mem_write (int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  mz_zip_reader_close (void*) ; 
 scalar_t__ mz_zip_reader_open (void*,int /*<<< orphan*/ ) ; 

int32_t mz_zip_reader_open_buffer(void *handle, uint8_t *buf, int32_t len, uint8_t copy)
{
    mz_zip_reader *reader = (mz_zip_reader *)handle;
    int32_t err = MZ_OK;

    mz_zip_reader_close(handle);

    mz_stream_mem_create(&reader->mem_stream);

    if (copy)
    {
        mz_stream_mem_set_grow_size(reader->mem_stream, len);
        mz_stream_mem_open(reader->mem_stream, NULL, MZ_OPEN_MODE_CREATE);
        mz_stream_mem_write(reader->mem_stream, buf, len);
        mz_stream_mem_seek(reader->mem_stream, 0, MZ_SEEK_SET);
    }
    else
    {
        mz_stream_mem_open(reader->mem_stream, NULL, MZ_OPEN_MODE_READ);
        mz_stream_mem_set_buffer(reader->mem_stream, buf, len);
    }

    if (err == MZ_OK)
        err = mz_zip_reader_open(handle, reader->mem_stream);

    return err;
}