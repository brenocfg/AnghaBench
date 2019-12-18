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
struct TYPE_2__ {int /*<<< orphan*/  split_stream; int /*<<< orphan*/  buffered_stream; int /*<<< orphan*/  file_stream; } ;
typedef  TYPE_1__ mz_zip_reader ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int /*<<< orphan*/  MZ_OPEN_MODE_READ ; 
 int /*<<< orphan*/  mz_stream_buffered_create (int /*<<< orphan*/ *) ; 
 scalar_t__ mz_stream_open (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_stream_os_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_stream_set_base (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_stream_split_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_zip_reader_close (void*) ; 
 scalar_t__ mz_zip_reader_open (void*,int /*<<< orphan*/ ) ; 

int32_t mz_zip_reader_open_file(void *handle, const char *path)
{
    mz_zip_reader *reader = (mz_zip_reader *)handle;
    int32_t err = MZ_OK;


    mz_zip_reader_close(handle);

    mz_stream_os_create(&reader->file_stream);
    mz_stream_buffered_create(&reader->buffered_stream);
    mz_stream_split_create(&reader->split_stream);

    mz_stream_set_base(reader->buffered_stream, reader->file_stream);
    mz_stream_set_base(reader->split_stream, reader->buffered_stream);

    err = mz_stream_open(reader->split_stream, path, MZ_OPEN_MODE_READ);
    if (err == MZ_OK)
        err = mz_zip_reader_open(handle, reader->split_stream);
    return err;
}