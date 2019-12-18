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
struct keyring_list {int /*<<< orphan*/  maxkeys; int /*<<< orphan*/  nkeys; } ;
struct TYPE_2__ {int /*<<< orphan*/  subscriptions; } ;
struct key {char* description; TYPE_1__ payload; } ;

/* Variables and functions */
 scalar_t__ key_is_instantiated (struct key const*) ; 
 struct keyring_list* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void keyring_describe(const struct key *keyring, struct seq_file *m)
{
	struct keyring_list *klist;

	if (keyring->description)
		seq_puts(m, keyring->description);
	else
		seq_puts(m, "[anon]");

	if (key_is_instantiated(keyring)) {
		rcu_read_lock();
		klist = rcu_dereference(keyring->payload.subscriptions);
		if (klist)
			seq_printf(m, ": %u/%u", klist->nkeys, klist->maxkeys);
		else
			seq_puts(m, ": empty");
		rcu_read_unlock();
	}
}