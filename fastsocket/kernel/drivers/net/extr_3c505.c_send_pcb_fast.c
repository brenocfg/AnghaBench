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
 int HCRE ; 
 int inb_status (unsigned int) ; 
 int /*<<< orphan*/  outb_command (unsigned char,unsigned int) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

__attribute__((used)) static inline bool send_pcb_fast(unsigned int base_addr, unsigned char byte)
{
	unsigned int timeout;
	outb_command(byte, base_addr);
	for (timeout = 0; timeout < 40000; timeout++) {
		if (inb_status(base_addr) & HCRE)
			return false;
	}
	pr_warning("3c505: send_pcb_fast timed out\n");
	return true;
}