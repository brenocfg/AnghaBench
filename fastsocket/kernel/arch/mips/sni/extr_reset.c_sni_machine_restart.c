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
 int /*<<< orphan*/  kb_wait () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  outb_p (int,int) ; 

void sni_machine_restart(char *command)
{
	int i, j;

	/* This does a normal via the keyboard controller like a PC.
	   We can do that easier ...  */
	local_irq_disable();
	for (;;) {
		for (i = 0; i < 100; i++) {
			kb_wait();
			for (j = 0; j < 100000 ; j++)
				/* nothing */;
			outb_p(0xfe, 0x64);	 /* pulse reset low */
		}
	}
}