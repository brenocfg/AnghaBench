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
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {scalar_t__ max_total_in; scalar_t__ total_in; int /*<<< orphan*/  total_out; TYPE_1__ stream; } ;
typedef  TYPE_2__ mz_stream_raw ;
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ mz_stream_read (int /*<<< orphan*/ ,void*,scalar_t__) ; 

int32_t mz_stream_raw_read(void *stream, void *buf, int32_t size)
{
    mz_stream_raw *raw = (mz_stream_raw *)stream;
    int32_t bytes_to_read = size;
    int32_t read = 0;

    if (raw->max_total_in > 0)
    {
        if ((int64_t)bytes_to_read > (raw->max_total_in - raw->total_in))
            bytes_to_read = (int32_t)(raw->max_total_in - raw->total_in);
    }

    read = mz_stream_read(raw->stream.base, buf, bytes_to_read);

    if (read > 0)
    {
        raw->total_in += read;
        raw->total_out += read;
    }

    return read;
}