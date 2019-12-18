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
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tw_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_frag_mem (struct net*) ; 
 int /*<<< orphan*/  ip_frag_nqueues (struct net*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int percpu_counter_sum_positive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_prot ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sock_prot_inuse_get (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_seq_show (struct seq_file*) ; 
 TYPE_1__ tcp_death_row ; 
 int /*<<< orphan*/  tcp_memory_allocated ; 
 int /*<<< orphan*/  tcp_orphan_count ; 
 int /*<<< orphan*/  tcp_prot ; 
 int /*<<< orphan*/  tcp_sockets_allocated ; 
 int /*<<< orphan*/  udp_memory_allocated ; 
 int /*<<< orphan*/  udp_prot ; 
 int /*<<< orphan*/  udplite_prot ; 

__attribute__((used)) static int sockstat_seq_show(struct seq_file *seq, void *v)
{
	struct net *net = seq->private;
	int orphans, sockets;

	local_bh_disable();
	orphans = percpu_counter_sum_positive(&tcp_orphan_count);
	sockets = percpu_counter_sum_positive(&tcp_sockets_allocated);
	local_bh_enable();

	socket_seq_show(seq);
	seq_printf(seq, "TCP: inuse %d orphan %d tw %d alloc %d mem %d\n",
		   sock_prot_inuse_get(net, &tcp_prot), orphans,
		   tcp_death_row.tw_count, sockets,
		   atomic_read(&tcp_memory_allocated));
	seq_printf(seq, "UDP: inuse %d mem %d\n",
		   sock_prot_inuse_get(net, &udp_prot),
		   atomic_read(&udp_memory_allocated));
	seq_printf(seq, "UDPLITE: inuse %d\n",
		   sock_prot_inuse_get(net, &udplite_prot));
	seq_printf(seq, "RAW: inuse %d\n",
		   sock_prot_inuse_get(net, &raw_prot));
	seq_printf(seq,  "FRAG: inuse %d memory %d\n",
			ip_frag_nqueues(net), ip_frag_mem(net));
	return 0;
}