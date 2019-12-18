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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ (* mz_stream_write_cb ) (void*,int /*<<< orphan*/ *,scalar_t__) ;
typedef  scalar_t__ (* mz_stream_read_cb ) (void*,int /*<<< orphan*/ *,int) ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 scalar_t__ MZ_STREAM_ERROR ; 
 scalar_t__ mz_stream_read (void*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mz_stream_write (void*,int /*<<< orphan*/ *,scalar_t__) ; 

int32_t mz_stream_copy_stream_to_end(void *target, mz_stream_write_cb write_cb, void *source,
    mz_stream_read_cb read_cb)
{
    uint8_t buf[16384];
    int32_t read = 0;
    int32_t written = 0;

    if (write_cb == NULL)
        write_cb = mz_stream_write;
    if (read_cb == NULL)
        read_cb = mz_stream_read;

    read = read_cb(source, buf, sizeof(buf));
    while (read > 0)
    {
        written = write_cb(target, buf, read);
        if (written != read)
            return MZ_STREAM_ERROR;
        read = read_cb(source, buf, sizeof(buf));
    }

    if (read < 0)
        return MZ_STREAM_ERROR;

    return MZ_OK;
}