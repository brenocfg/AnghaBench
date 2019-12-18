#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pt_regs {unsigned long* gpr; int /*<<< orphan*/  nip; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 scalar_t__ scanhex (unsigned long*) ; 
 int /*<<< orphan*/  scannl () ; 
 int /*<<< orphan*/  xmon_show_stack (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void backtrace(struct pt_regs *excp)
{
	unsigned long sp;

	if (scanhex(&sp))
		xmon_show_stack(sp, 0, 0);
	else
		xmon_show_stack(excp->gpr[1], excp->link, excp->nip);
	scannl();
}