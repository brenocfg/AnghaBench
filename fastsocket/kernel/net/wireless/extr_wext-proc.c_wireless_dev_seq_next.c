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
struct seq_file {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 void* first_net_device (struct net*) ; 
 void* next_net_device (void*) ; 
 struct net* seq_file_net (struct seq_file*) ; 

__attribute__((used)) static void *wireless_dev_seq_next(struct seq_file *seq, void *v, loff_t *pos)
{
	struct net *net = seq_file_net(seq);

	++*pos;

	return v == SEQ_START_TOKEN ?
		first_net_device(net) : next_net_device(v);
}