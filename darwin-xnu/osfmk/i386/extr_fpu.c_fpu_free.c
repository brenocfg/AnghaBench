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
typedef  int /*<<< orphan*/  thread_t ;
typedef  TYPE_1__* pcb_t ;
struct TYPE_3__ {int /*<<< orphan*/  xstate; } ;

/* Variables and functions */
 TYPE_1__* THREAD_TO_PCB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNDEFINED ; 
 int /*<<< orphan*/  fp_state_free (void*,int /*<<< orphan*/ ) ; 

void
fpu_free(thread_t thread, void *fps)
{
	pcb_t	pcb = THREAD_TO_PCB(thread);
	
	fp_state_free(fps, pcb->xstate);
	pcb->xstate = UNDEFINED;
}