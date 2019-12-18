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
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {int /*<<< orphan*/  total_out; scalar_t__ buffer; TYPE_1__ stream; int /*<<< orphan*/  hmac; } ;
typedef  TYPE_2__ mz_stream_wzaes ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_PARAM_ERROR ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  mz_crypt_hmac_update (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ mz_stream_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mz_stream_wzaes_ctr_encrypt (void*,int /*<<< orphan*/ *,scalar_t__) ; 

int32_t mz_stream_wzaes_write(void *stream, const void *buf, int32_t size)
{
    mz_stream_wzaes *wzaes = (mz_stream_wzaes *)stream;
    const uint8_t *buf_ptr = (const uint8_t *)buf;
    int32_t bytes_to_write = sizeof(wzaes->buffer);
    int32_t total_written = 0;
    int32_t written = 0;

    if (size < 0)
        return MZ_PARAM_ERROR;

    do
    {
        if (bytes_to_write > (size - total_written))
            bytes_to_write = (size - total_written);

        memcpy(wzaes->buffer, buf_ptr, bytes_to_write);
        buf_ptr += bytes_to_write;

        mz_stream_wzaes_ctr_encrypt(stream, (uint8_t *)wzaes->buffer, bytes_to_write);
        mz_crypt_hmac_update(wzaes->hmac, wzaes->buffer, bytes_to_write);

        written = mz_stream_write(wzaes->stream.base, wzaes->buffer, bytes_to_write);
        if (written < 0)
            return written;

        total_written += written;
    }
    while (total_written < size && written > 0);

    wzaes->total_out += total_written;
    return total_written;
}