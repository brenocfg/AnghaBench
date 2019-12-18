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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  Z8530_PORT_OF (unsigned long) ; 
 unsigned long Z8530_PORT_SLEEP ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline int z8530_read_port(unsigned long p)
{
	u8 r=inb(Z8530_PORT_OF(p));
	if(p&Z8530_PORT_SLEEP)	/* gcc should figure this out efficiently ! */
		udelay(5);
	return r;
}