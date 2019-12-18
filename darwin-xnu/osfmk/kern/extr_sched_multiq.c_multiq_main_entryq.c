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
typedef  TYPE_2__* processor_t ;
typedef  int /*<<< orphan*/  entry_queue_t ;
struct TYPE_5__ {TYPE_1__* processor_set; } ;
struct TYPE_4__ {int /*<<< orphan*/  pset_runq; } ;

/* Variables and functions */

__attribute__((used)) __attribute__((always_inline))
static inline entry_queue_t
multiq_main_entryq(processor_t processor)
{
	return (entry_queue_t)&processor->processor_set->pset_runq;
}