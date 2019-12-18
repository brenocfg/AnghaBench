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
struct TYPE_3__ {int rb_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  seq_head; TYPE_1__ root; } ;
struct btrfs_transaction {TYPE_2__ delayed_refs; int /*<<< orphan*/  list; int /*<<< orphan*/  use_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_transaction_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct btrfs_transaction*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct btrfs_transaction*,int /*<<< orphan*/ ,int) ; 

void put_transaction(struct btrfs_transaction *transaction)
{
	WARN_ON(atomic_read(&transaction->use_count) == 0);
	if (atomic_dec_and_test(&transaction->use_count)) {
		BUG_ON(!list_empty(&transaction->list));
		WARN_ON(transaction->delayed_refs.root.rb_node);
		WARN_ON(!list_empty(&transaction->delayed_refs.seq_head));
		memset(transaction, 0, sizeof(*transaction));
		kmem_cache_free(btrfs_transaction_cachep, transaction);
	}
}