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
struct net_local {int OpenCommandIssued; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OC_OPEN ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tms380tr_exec_cmd (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tms380tr_open_adapter(struct net_device *dev)
{
	struct net_local *tp = netdev_priv(dev);

	if(tp->OpenCommandIssued)
		return;

	tp->OpenCommandIssued = 1;
	tms380tr_exec_cmd(dev, OC_OPEN);

	return;
}