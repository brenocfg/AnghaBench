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
 int getpgrp () ; 
 int /*<<< orphan*/  register_winch_irq (int,int,int,void*,int /*<<< orphan*/ ) ; 

int is_skas_winch(int pid, int fd, void *data)
{
	if (pid != getpgrp())
		return 0;

	register_winch_irq(-1, fd, -1, data, 0);
	return 1;
}