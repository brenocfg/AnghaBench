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
struct isp116x {int /*<<< orphan*/  addr_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_TEST () ; 
 int /*<<< orphan*/  isp116x_delay (struct isp116x*,int) ; 
 int /*<<< orphan*/  writew (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void isp116x_write_addr(struct isp116x *isp116x, unsigned reg)
{
	IRQ_TEST();
	writew(reg & 0xff, isp116x->addr_reg);
	isp116x_delay(isp116x, 300);
}