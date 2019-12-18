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
struct l3_process {int dummy; } ;
struct TYPE_2__ {long data; void* function; } ;
struct L3Timer {TYPE_1__ tl; struct l3_process* pc; } ;

/* Variables and functions */
 scalar_t__ L3ExpireTimer ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 

void
L3InitTimer(struct l3_process *pc, struct L3Timer *t)
{
	t->pc = pc;
	t->tl.function = (void *) L3ExpireTimer;
	t->tl.data = (long) t;
	init_timer(&t->tl);
}