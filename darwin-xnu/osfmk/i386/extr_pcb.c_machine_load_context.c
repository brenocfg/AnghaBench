#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
struct TYPE_6__ {int /*<<< orphan*/  specFlags; } ;
struct TYPE_7__ {TYPE_1__ machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  Load_context (TYPE_2__*) ; 
 int /*<<< orphan*/  OnProc ; 
 int /*<<< orphan*/  act_machine_switch_pcb (int /*<<< orphan*/ *,TYPE_2__*) ; 

void
machine_load_context(
	thread_t		new)
{
	new->machine.specFlags |= OnProc;
	act_machine_switch_pcb(NULL, new);
	Load_context(new);
}