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
struct TYPE_2__ {int /*<<< orphan*/  position; } ;
typedef  TYPE_1__ mz_stream_mem ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */

int64_t mz_stream_mem_tell(void *stream)
{
    mz_stream_mem *mem = (mz_stream_mem *)stream;
    return mem->position;
}