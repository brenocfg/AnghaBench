#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct net* private; } ;
struct TYPE_3__ {scalar_t__ xfrm_statistics; } ;
struct net {TYPE_1__ mib; } ;
struct TYPE_4__ {int /*<<< orphan*/  entry; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_fold_field (void**,int /*<<< orphan*/ ) ; 
 TYPE_2__* xfrm_mib_list ; 

__attribute__((used)) static int xfrm_statistics_seq_show(struct seq_file *seq, void *v)
{
	struct net *net = seq->private;
	int i;
	for (i=0; xfrm_mib_list[i].name; i++)
		seq_printf(seq, "%-24s\t%lu\n", xfrm_mib_list[i].name,
			   snmp_fold_field((void **)net->mib.xfrm_statistics,
					   xfrm_mib_list[i].entry));
	return 0;
}