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
struct mdio_if_info {int (* mdio_read ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ;int (* mdio_write ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 

int mdio_set_flag(const struct mdio_if_info *mdio,
		  int prtad, int devad, u16 addr, int mask,
		  bool sense)
{
	int old_val = mdio->mdio_read(mdio->dev, prtad, devad, addr);
	int new_val;

	if (old_val < 0)
		return old_val;
	if (sense)
		new_val = old_val | mask;
	else
		new_val = old_val & ~mask;
	if (old_val == new_val)
		return 0;
	return mdio->mdio_write(mdio->dev, prtad, devad, addr, new_val);
}