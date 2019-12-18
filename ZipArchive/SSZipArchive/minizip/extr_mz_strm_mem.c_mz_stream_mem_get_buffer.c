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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  mz_stream_mem_get_buffer_at (void*,int /*<<< orphan*/ ,void const**) ; 

int32_t mz_stream_mem_get_buffer(void *stream, const void **buf)
{
    return mz_stream_mem_get_buffer_at(stream, 0, buf);
}