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
 int host_read_unsafe (unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int host_read_ctrl_unsafe(unsigned io_base, unsigned timeout)
{
	int data;

	while (((data = host_read_unsafe(io_base)) < 0) && (timeout != 0)) {
		udelay(100);
		--timeout;
	} /* while */

	return data;
}