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
struct seq_file {struct net* private; } ;
struct TYPE_2__ {scalar_t__ icmpmsg_statistics; } ;
struct net {TYPE_1__ mib; } ;

/* Variables and functions */
 int ICMPMSG_MIB_MAX ; 
 int PERLINE ; 
 int /*<<< orphan*/  icmpmsg_put_line (struct seq_file*,unsigned long*,unsigned short*,int) ; 
 unsigned long snmp_fold_field (void**,int) ; 

__attribute__((used)) static void icmpmsg_put(struct seq_file *seq)
{
#define PERLINE	16

	int i, count;
	unsigned short type[PERLINE];
	unsigned long vals[PERLINE], val;
	struct net *net = seq->private;

	count = 0;
	for (i = 0; i < ICMPMSG_MIB_MAX; i++) {
		val = snmp_fold_field((void **) net->mib.icmpmsg_statistics, i);
		if (val) {
			type[count] = i;
			vals[count++] = val;
		}
		if (count == PERLINE) {
			icmpmsg_put_line(seq, vals, type, count);
			count = 0;
		}
	}
	icmpmsg_put_line(seq, vals, type, count);

#undef PERLINE
}