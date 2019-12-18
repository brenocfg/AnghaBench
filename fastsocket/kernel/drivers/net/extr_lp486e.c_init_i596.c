#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_8__ {scalar_t__ command; } ;
struct TYPE_7__ {int /*<<< orphan*/  command; } ;
struct TYPE_6__ {int /*<<< orphan*/  command; } ;
struct TYPE_5__ {int /*<<< orphan*/  command; } ;
struct i596_private {TYPE_4__ scb; TYPE_3__ tdr; TYPE_2__ set_add; scalar_t__ eth_addr; TYPE_1__ set_conf; scalar_t__ i596_config; } ;
typedef  void i596_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CA () ; 
 int /*<<< orphan*/  CmdConfigure ; 
 int /*<<< orphan*/  CmdIASetup ; 
 int /*<<< orphan*/  CmdTDR ; 
 scalar_t__ RX_START ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  i596_add_cmd (struct net_device*,void*) ; 
 scalar_t__ i596_scp_setup (struct net_device*) ; 
 scalar_t__ i596_timeout (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  init_setup ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 struct i596_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
init_i596(struct net_device *dev) {
	struct i596_private *lp;

	if (i596_scp_setup(dev))
		return 1;

	lp = netdev_priv(dev);
	lp->scb.command = 0;

	memcpy ((void *)lp->i596_config, init_setup, 14);
	lp->set_conf.command = CmdConfigure;
	i596_add_cmd(dev, (void *)&lp->set_conf);

	memcpy ((void *)lp->eth_addr, dev->dev_addr, 6);
	lp->set_add.command = CmdIASetup;
	i596_add_cmd(dev, (struct i596_cmd *)&lp->set_add);

	lp->tdr.command = CmdTDR;
	i596_add_cmd(dev, (struct i596_cmd *)&lp->tdr);

	if (lp->scb.command && i596_timeout(dev, "i82596 init", 200))
		return 1;

	lp->scb.command = RX_START;
	CA();

	barrier();

	if (lp->scb.command && i596_timeout(dev, "Receive Unit start", 100))
		return 1;

	return 0;
}