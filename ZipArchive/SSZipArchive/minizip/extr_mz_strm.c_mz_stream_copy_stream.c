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
typedef  scalar_t__ (* mz_stream_read_cb ) (void*,int /*<<< orphan*/ *,scalar_t__) ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 scalar_t__ MZ_STREAM_ERROR ; 
 scalar_t__ mz_stream_read (void*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ mz_stream_write (void*,int /*<<< orphan*/ *,scalar_t__) ; 

int32_t mz_stream_copy_stream(void *target, mz_stream_write_cb write_cb, void *source,
    mz_stream_read_cb read_cb, int32_t len)
{
    uint8_t buf[16384];
    int32_t bytes_to_copy = 0;
    int32_t read = 0;
    int32_t written = 0;

    if (write_cb == NULL)
        write_cb = mz_stream_write;
    if (read_cb == NULL)
        read_cb = mz_stream_read;

    while (len > 0)
    {
        bytes_to_copy = len;
        if (bytes_to_copy > (int32_t)sizeof(buf))
            bytes_to_copy = sizeof(buf);
        read = read_cb(source, buf, bytes_to_copy);
        if (read <= 0)
            return MZ_STREAM_ERROR;
        written = write_cb(target, buf, read);
        if (written != read)
            return MZ_STREAM_ERROR;
        len -= read;
    }

    return MZ_OK;
}