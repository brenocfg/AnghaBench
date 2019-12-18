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

/* Variables and functions */
 int /*<<< orphan*/  _machine_halt () ; 
 int /*<<< orphan*/  rbtx4927_softreset_addr ; 
 int /*<<< orphan*/  rbtx4927_softresetlock_addr ; 
 int readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void toshiba_rbtx4927_restart(char *command)
{
	/* enable the s/w reset register */
	writeb(1, rbtx4927_softresetlock_addr);

	/* wait for enable to be seen */
	while (!(readb(rbtx4927_softresetlock_addr) & 1))
		;

	/* do a s/w reset */
	writeb(1, rbtx4927_softreset_addr);

	/* fallback */
	(*_machine_halt)();
}