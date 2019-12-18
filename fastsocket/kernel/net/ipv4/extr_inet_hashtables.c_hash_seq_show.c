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
struct inet_hash_stats {int /*<<< orphan*/  global_accept; int /*<<< orphan*/  remote_accept; int /*<<< orphan*/  local_accept; int /*<<< orphan*/  common_accept; int /*<<< orphan*/  global_listen_lookup; int /*<<< orphan*/  local_listen_lookup; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_id ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hash_seq_show(struct seq_file *seq, void *v)
{
	struct inet_hash_stats *s = v;

	seq_printf(seq, "%u\t%-15lu%-15lu%-15lu%-15lu%-15lu%-15lu\n",
		cpu_id, s->local_listen_lookup, s->global_listen_lookup,
		s->common_accept, s->local_accept, s->remote_accept, s->global_accept);

	return 0;
}