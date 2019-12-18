#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_2__* thread_t ;
struct TYPE_4__ {int /*<<< orphan*/  thread_gpu_ns; } ;
struct TYPE_5__ {TYPE_1__ machine; } ;

/* Variables and functions */

uint64_t
ml_gpu_stat(thread_t t) {
	return t->machine.thread_gpu_ns;
}