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
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
struct net {TYPE_1__ ct; } ;
struct ip_conntrack_stat {int /*<<< orphan*/  expect_delete; int /*<<< orphan*/  expect_create; int /*<<< orphan*/  expect_new; int /*<<< orphan*/  error; int /*<<< orphan*/  early_drop; int /*<<< orphan*/  drop; int /*<<< orphan*/  insert_failed; int /*<<< orphan*/  insert; int /*<<< orphan*/  delete_list; int /*<<< orphan*/  delete; int /*<<< orphan*/  ignore; int /*<<< orphan*/  invalid; int /*<<< orphan*/  new; int /*<<< orphan*/  found; int /*<<< orphan*/  searched; } ;

/* Variables and functions */
 void* SEQ_START_TOKEN ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 struct net* seq_file_net (struct seq_file*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int ct_cpu_seq_show(struct seq_file *seq, void *v)
{
	struct net *net = seq_file_net(seq);
	unsigned int nr_conntracks = atomic_read(&net->ct.count);
	const struct ip_conntrack_stat *st = v;

	if (v == SEQ_START_TOKEN) {
		seq_printf(seq, "entries  searched found new invalid ignore delete delete_list insert insert_failed drop early_drop icmp_error  expect_new expect_create expect_delete\n");
		return 0;
	}

	seq_printf(seq, "%08x  %08x %08x %08x %08x %08x %08x %08x "
			"%08x %08x %08x %08x %08x  %08x %08x %08x \n",
		   nr_conntracks,
		   st->searched,
		   st->found,
		   st->new,
		   st->invalid,
		   st->ignore,
		   st->delete,
		   st->delete_list,
		   st->insert,
		   st->insert_failed,
		   st->drop,
		   st->early_drop,
		   st->error,

		   st->expect_new,
		   st->expect_create,
		   st->expect_delete
		);
	return 0;
}