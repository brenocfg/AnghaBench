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
struct net_device {int dummy; } ;
struct ethtool_regs {int /*<<< orphan*/  len; } ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LANCER_FW_DUMP_FILE ; 
 int /*<<< orphan*/  be_cmd_get_regs (struct be_adapter*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ be_physfn (struct be_adapter*) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 
 int /*<<< orphan*/  lancer_cmd_read_file (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
be_get_regs(struct net_device *netdev, struct ethtool_regs *regs, void *buf)
{
	struct be_adapter *adapter = netdev_priv(netdev);

	if (be_physfn(adapter)) {
		memset(buf, 0, regs->len);
		if (lancer_chip(adapter))
			lancer_cmd_read_file(adapter, LANCER_FW_DUMP_FILE,
					regs->len, buf);
		else
			be_cmd_get_regs(adapter, regs->len, buf);
	}
}