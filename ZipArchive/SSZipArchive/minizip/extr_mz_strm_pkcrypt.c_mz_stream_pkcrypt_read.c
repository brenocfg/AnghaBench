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
struct TYPE_4__ {scalar_t__ max_total_in; scalar_t__ total_in; TYPE_1__ stream; } ;
typedef  TYPE_2__ mz_stream_pkcrypt ;
typedef  scalar_t__ int64_t ;
typedef  size_t int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  mz_stream_pkcrypt_decode (void*,int /*<<< orphan*/ ) ; 
 size_t mz_stream_read (int /*<<< orphan*/ ,void*,size_t) ; 

int32_t mz_stream_pkcrypt_read(void *stream, void *buf, int32_t size)
{
    mz_stream_pkcrypt *pkcrypt = (mz_stream_pkcrypt *)stream;
    uint8_t *buf_ptr = (uint8_t *)buf;
    int32_t bytes_to_read = size;
    int32_t read = 0;
    int32_t i = 0;


    if ((int64_t)bytes_to_read > (pkcrypt->max_total_in - pkcrypt->total_in))
        bytes_to_read = (int32_t)(pkcrypt->max_total_in - pkcrypt->total_in);

    read = mz_stream_read(pkcrypt->stream.base, buf, bytes_to_read);

    for (i = 0; i < read; i++)
        buf_ptr[i] = mz_stream_pkcrypt_decode(stream, buf_ptr[i]);

    if (read > 0)
        pkcrypt->total_in += read;

    return read;
}