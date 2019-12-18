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
struct seq_file {struct ap_data* private; } ;
struct ap_data {int bridged_unicast; int bridged_multicast; int max_inactivity; int bridge_packets; int nullfunc_ack; int autom_ap_wds; int tx_drop_nonassoc; TYPE_1__* local; } ;
struct TYPE_2__ {int auth_algs; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 

__attribute__((used)) static int ap_debug_proc_show(struct seq_file *m, void *v)
{
	struct ap_data *ap = m->private;

	seq_printf(m, "BridgedUnicastFrames=%u\n", ap->bridged_unicast);
	seq_printf(m, "BridgedMulticastFrames=%u\n", ap->bridged_multicast);
	seq_printf(m, "max_inactivity=%u\n", ap->max_inactivity / HZ);
	seq_printf(m, "bridge_packets=%u\n", ap->bridge_packets);
	seq_printf(m, "nullfunc_ack=%u\n", ap->nullfunc_ack);
	seq_printf(m, "autom_ap_wds=%u\n", ap->autom_ap_wds);
	seq_printf(m, "auth_algs=%u\n", ap->local->auth_algs);
	seq_printf(m, "tx_drop_nonassoc=%u\n", ap->tx_drop_nonassoc);
	return 0;
}