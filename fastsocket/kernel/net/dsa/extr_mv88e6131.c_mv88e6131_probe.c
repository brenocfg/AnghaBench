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
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_PORT (int /*<<< orphan*/ ) ; 
 int __mv88e6xxx_reg_read (struct mii_bus*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *mv88e6131_probe(struct mii_bus *bus, int sw_addr)
{
	int ret;

	ret = __mv88e6xxx_reg_read(bus, sw_addr, REG_PORT(0), 0x03);
	if (ret >= 0) {
		ret &= 0xfff0;
		if (ret == 0x0950)
			return "Marvell 88E6095/88E6095F";
		if (ret == 0x1060)
			return "Marvell 88E6131";
	}

	return NULL;
}