#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ reset; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* redo ) () ;int /*<<< orphan*/  (* error ) () ;} ;

/* Variables and functions */
 TYPE_2__* FDCS ; 
 TYPE_1__* cont ; 
 int /*<<< orphan*/  debugt (char*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/  (*) ()) ; 
 int /*<<< orphan*/  result () ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static void reset_interrupt(void)
{
	debugt("reset interrupt:");
	result();		/* get the status ready for set_fdc */
	if (FDCS->reset) {
		printk("reset set in interrupt, calling %p\n", cont->error);
		cont->error();	/* a reset just after a reset. BAD! */
	}
	cont->redo();
}