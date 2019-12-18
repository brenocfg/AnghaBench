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
struct net_local {unsigned short CMDqueue; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tms380tr_chk_outstanding_cmds (struct net_device*) ; 

__attribute__((used)) static void tms380tr_exec_cmd(struct net_device *dev, unsigned short Command)
{
	struct net_local *tp = netdev_priv(dev);

	tp->CMDqueue |= Command;
	tms380tr_chk_outstanding_cmds(dev);

	return;
}