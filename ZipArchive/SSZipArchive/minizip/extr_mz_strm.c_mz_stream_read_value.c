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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_END_OF_STREAM ; 
 scalar_t__ MZ_OK ; 
 scalar_t__ MZ_STREAM_ERROR ; 
 scalar_t__ mz_stream_error (void*) ; 
 scalar_t__ mz_stream_read (void*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static int32_t mz_stream_read_value(void *stream, uint64_t *value, int32_t len)
{
    uint8_t buf[8];
    int32_t n = 0;
    int32_t i = 0;

    *value = 0;
    if (mz_stream_read(stream, buf, len) == len)
    {
        for (n = 0; n < len; n += 1, i += 8)
            *value += ((uint64_t)buf[n]) << i;
    }
    else if (mz_stream_error(stream))
        return MZ_STREAM_ERROR;
    else
        return MZ_END_OF_STREAM;

    return MZ_OK;
}