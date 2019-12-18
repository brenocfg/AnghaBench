#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct proc_dir_entry {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  proc_net_devsnmp6; } ;
struct net {TYPE_2__ mib; } ;
struct TYPE_4__ {struct proc_dir_entry* proc_dir_entry; } ;
struct inet6_dev {TYPE_1__ stats; TYPE_3__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  S_IRUGO ; 
 struct net* dev_net (TYPE_3__*) ; 
 struct proc_dir_entry* proc_create_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct inet6_dev*) ; 
 int /*<<< orphan*/  snmp6_dev_seq_fops ; 

int snmp6_register_dev(struct inet6_dev *idev)
{
	struct proc_dir_entry *p;
	struct net *net;

	if (!idev || !idev->dev)
		return -EINVAL;

	net = dev_net(idev->dev);
	if (!net->mib.proc_net_devsnmp6)
		return -ENOENT;

	p = proc_create_data(idev->dev->name, S_IRUGO,
			     net->mib.proc_net_devsnmp6,
			     &snmp6_dev_seq_fops, idev);
	if (!p)
		return -ENOMEM;

	idev->stats.proc_dir_entry = p;
	return 0;
}