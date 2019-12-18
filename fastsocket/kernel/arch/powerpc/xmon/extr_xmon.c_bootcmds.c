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
struct TYPE_2__ {int /*<<< orphan*/  (* power_off ) () ;int /*<<< orphan*/  (* halt ) () ;int /*<<< orphan*/  (* restart ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int inchar () ; 
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 () ; 

__attribute__((used)) static void bootcmds(void)
{
	int cmd;

	cmd = inchar();
	if (cmd == 'r')
		ppc_md.restart(NULL);
	else if (cmd == 'h')
		ppc_md.halt();
	else if (cmd == 'p')
		ppc_md.power_off();
}