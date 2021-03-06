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
struct dsa_switch {int /*<<< orphan*/  master_mii_bus; } ;

/* Variables and functions */
 int mdiobus_read (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int reg_read(struct dsa_switch *ds, int addr, int reg)
{
	return mdiobus_read(ds->master_mii_bus, addr, reg);
}