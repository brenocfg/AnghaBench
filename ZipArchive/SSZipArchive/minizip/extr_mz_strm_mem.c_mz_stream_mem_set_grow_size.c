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
struct TYPE_2__ {int /*<<< orphan*/  grow_size; } ;
typedef  TYPE_1__ mz_stream_mem ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */

void mz_stream_mem_set_grow_size(void *stream, int32_t grow_size)
{
    mz_stream_mem *mem = (mz_stream_mem *)stream;
    mem->grow_size = grow_size;
}