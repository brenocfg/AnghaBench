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
struct TYPE_3__ {int /*<<< orphan*/  nub; int /*<<< orphan*/  target; int /*<<< orphan*/  (* handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ i386_interrupt_handler_t ;

/* Variables and functions */
 TYPE_1__ PE_interrupt_handler ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
PE_incoming_interrupt(int interrupt)
{
	i386_interrupt_handler_t	*vector;

	vector = &PE_interrupt_handler;

#if CONFIG_DTRACE && DEVELOPMENT
        DTRACE_INT5(interrupt_start, void *, vector->nub, int, 0, 
                    void *, vector->target, IOInterruptHandler, vector->handler,
                    void *, vector->refCon);
#endif

	vector->handler(vector->target, NULL, vector->nub, interrupt);

#if CONFIG_DTRACE && DEVELOPMENT
        DTRACE_INT5(interrupt_complete, void *, vector->nub, int, 0, 
                    void *, vector->target, IOInterruptHandler, vector->handler,
                    void *, vector->refCon);
#endif
}