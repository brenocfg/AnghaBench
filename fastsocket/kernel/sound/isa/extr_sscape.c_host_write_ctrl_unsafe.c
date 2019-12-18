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
 int host_write_unsafe (unsigned int,unsigned char) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int host_write_ctrl_unsafe(unsigned io_base, unsigned char data,
                                  unsigned timeout)
{
	int err;

	while (!(err = host_write_unsafe(io_base, data)) && (timeout != 0)) {
		udelay(100);
		--timeout;
	} /* while */

	return err;
}