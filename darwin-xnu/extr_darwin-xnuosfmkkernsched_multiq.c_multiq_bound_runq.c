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
typedef  int /*<<< orphan*/ * run_queue_t ;
typedef  TYPE_1__* processor_t ;
struct TYPE_3__ {int /*<<< orphan*/  runq; } ;

/* Variables and functions */

__attribute__((used)) __attribute__((always_inline))
static inline run_queue_t
multiq_bound_runq(processor_t processor)
{
	return &processor->runq;
}