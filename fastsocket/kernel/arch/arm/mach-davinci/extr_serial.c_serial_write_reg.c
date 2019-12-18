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
struct plat_serial8250_port {int regshift; int /*<<< orphan*/  mapbase; } ;

/* Variables and functions */
 scalar_t__ IO_ADDRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 

__attribute__((used)) static inline void serial_write_reg(struct plat_serial8250_port *p, int offset,
				    int value)
{
	offset <<= p->regshift;
	__raw_writel(value, IO_ADDRESS(p->mapbase) + offset);
}