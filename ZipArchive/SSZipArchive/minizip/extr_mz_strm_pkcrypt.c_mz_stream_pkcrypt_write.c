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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int /*<<< orphan*/  total_out; int /*<<< orphan*/ * buffer; TYPE_1__ stream; } ;
typedef  TYPE_2__ mz_stream_pkcrypt ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  mz_stream_pkcrypt_encode (void*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 scalar_t__ mz_stream_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

int32_t mz_stream_pkcrypt_write(void *stream, const void *buf, int32_t size)
{
    mz_stream_pkcrypt *pkcrypt = (mz_stream_pkcrypt *)stream;
    const uint8_t *buf_ptr = (const uint8_t *)buf;
    int32_t bytes_to_write = sizeof(pkcrypt->buffer);
    int32_t total_written = 0;
    int32_t written = 0;
    int32_t i = 0;
    uint16_t t = 0;

    if (size < 0)
        return MZ_PARAM_ERROR;

    do
    {
        if (bytes_to_write > (size - total_written))
            bytes_to_write = (size - total_written);

        for (i = 0; i < bytes_to_write; i += 1)
        {
            pkcrypt->buffer[i] = mz_stream_pkcrypt_encode(stream, *buf_ptr, t);
            buf_ptr += 1;
        }

        written = mz_stream_write(pkcrypt->stream.base, pkcrypt->buffer, bytes_to_write);
        if (written < 0)
            return written;

        total_written += written;
    }
    while (total_written < size && written > 0);

    pkcrypt->total_out += total_written;
    return total_written;
}