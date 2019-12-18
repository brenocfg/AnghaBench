#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct mii_bus {struct mdiobb_ctrl* priv; } ;
struct mdiobb_ctrl {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_mdio_dir ) (struct mdiobb_ctrl*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_WRITE ; 
 int /*<<< orphan*/  mdiobb_cmd (struct mdiobb_ctrl*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mdiobb_get_bit (struct mdiobb_ctrl*) ; 
 int /*<<< orphan*/  mdiobb_send_bit (struct mdiobb_ctrl*,int) ; 
 int /*<<< orphan*/  mdiobb_send_num (struct mdiobb_ctrl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct mdiobb_ctrl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdiobb_write(struct mii_bus *bus, int phy, int reg, u16 val)
{
	struct mdiobb_ctrl *ctrl = bus->priv;

	mdiobb_cmd(ctrl, MDIO_WRITE, phy, reg);

	/* send the turnaround (10) */
	mdiobb_send_bit(ctrl, 1);
	mdiobb_send_bit(ctrl, 0);

	mdiobb_send_num(ctrl, val, 16);

	ctrl->ops->set_mdio_dir(ctrl, 0);
	mdiobb_get_bit(ctrl);
	return 0;
}