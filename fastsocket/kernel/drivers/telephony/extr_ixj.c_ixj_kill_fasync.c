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
struct TYPE_3__ {scalar_t__* ixj_signals; int /*<<< orphan*/  async_queue; } ;
typedef  size_t IXJ_SIGEVENT ;
typedef  TYPE_1__ IXJ ;

/* Variables and functions */
 int ixjdebug ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  printk (char*,size_t) ; 

__attribute__((used)) static inline void ixj_kill_fasync(IXJ *j, IXJ_SIGEVENT event, int dir)
{
	if(j->ixj_signals[event]) {
		if(ixjdebug & 0x0100)
			printk("Sending signal for event %d\n", event);
			/* Send apps notice of change */
		/* see config.h for macro definition */
		kill_fasync(&(j->async_queue), j->ixj_signals[event], dir);
	}
}