#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_1__* thread_t ;
struct TYPE_3__ {int /*<<< orphan*/  kperf_flags; } ;

/* Variables and functions */

void
kperf_set_thread_flags(thread_t thread, uint32_t flags)
{
	thread->kperf_flags = flags;
}