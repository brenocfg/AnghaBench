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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat; } ;
struct net {TYPE_1__ ct; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_possible (int) ; 
 int nr_cpu_ids ; 
 void* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 struct net* seq_file_net (struct seq_file*) ; 

__attribute__((used)) static void *ct_cpu_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
	struct net *net = seq_file_net(seq);
	int cpu;

	for (cpu = *pos; cpu < nr_cpu_ids; ++cpu) {
		if (!cpu_possible(cpu))
			continue;
		*pos = cpu+1;
		return per_cpu_ptr(net->ct.stat, cpu);
	}

	return NULL;
}