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
struct TYPE_3__ {int /*<<< orphan*/  pc; int /*<<< orphan*/  th; } ;
typedef  TYPE_1__ ctrace_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTRACE_STACK_SIZE ; 
 int /*<<< orphan*/  OSBacktrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_thread () ; 

void
ctrace_record(ctrace_t *tr)
{
	tr->th = current_thread();
	bzero(tr->pc, sizeof (tr->pc));
	(void) OSBacktrace(tr->pc, CTRACE_STACK_SIZE);
}