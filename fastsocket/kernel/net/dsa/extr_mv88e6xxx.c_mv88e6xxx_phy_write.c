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
typedef  int /*<<< orphan*/  u16 ;
struct dsa_switch {int dummy; } ;

/* Variables and functions */
 int mv88e6xxx_reg_write (struct dsa_switch*,int,int,int /*<<< orphan*/ ) ; 

int mv88e6xxx_phy_write(struct dsa_switch *ds, int addr, int regnum, u16 val)
{
	if (addr >= 0)
		return mv88e6xxx_reg_write(ds, addr, regnum, val);
	return 0;
}