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
struct TYPE_2__ {int /*<<< orphan*/  proc_net_devsnmp6; } ;
struct net {TYPE_1__ mib; int /*<<< orphan*/  proc_net; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  proc_mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_net_fops_create (struct net*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_net_remove (struct net*,char*) ; 
 int /*<<< orphan*/  snmp6_seq_fops ; 
 int /*<<< orphan*/  sockstat6_seq_fops ; 

__attribute__((used)) static int ipv6_proc_init_net(struct net *net)
{
	if (!proc_net_fops_create(net, "sockstat6", S_IRUGO,
			&sockstat6_seq_fops))
		return -ENOMEM;

	if (!proc_net_fops_create(net, "snmp6", S_IRUGO, &snmp6_seq_fops))
		goto proc_snmp6_fail;

	net->mib.proc_net_devsnmp6 = proc_mkdir("dev_snmp6", net->proc_net);
	if (!net->mib.proc_net_devsnmp6)
		goto proc_dev_snmp6_fail;
	return 0;

proc_snmp6_fail:
	proc_net_remove(net, "sockstat6");
proc_dev_snmp6_fail:
	proc_net_remove(net, "dev_snmp6");
	return -ENOMEM;
}