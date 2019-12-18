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
struct parport {int dummy; } ;

/* Variables and functions */
 unsigned int parport_ip32_read_econtrol (struct parport*) ; 
 int /*<<< orphan*/  parport_ip32_write_econtrol (struct parport*,unsigned int) ; 

__attribute__((used)) static inline void parport_ip32_frob_econtrol(struct parport *p,
					      unsigned int mask,
					      unsigned int val)
{
	unsigned int c;
	c = (parport_ip32_read_econtrol(p) & ~mask) ^ val;
	parport_ip32_write_econtrol(p, c);
}