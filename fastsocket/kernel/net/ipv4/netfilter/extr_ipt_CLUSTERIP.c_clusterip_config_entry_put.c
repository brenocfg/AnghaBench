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
struct clusterip_config {TYPE_1__* pde; int /*<<< orphan*/  dev; int /*<<< orphan*/  clustermac; int /*<<< orphan*/  list; int /*<<< orphan*/  entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clusterip_lock ; 
 int /*<<< orphan*/  dev_mc_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
clusterip_config_entry_put(struct clusterip_config *c)
{
	write_lock_bh(&clusterip_lock);
	if (atomic_dec_and_test(&c->entries)) {
		list_del(&c->list);
		write_unlock_bh(&clusterip_lock);

		dev_mc_delete(c->dev, c->clustermac, ETH_ALEN, 0);
		dev_put(c->dev);

		/* In case anyone still accesses the file, the open/close
		 * functions are also incrementing the refcount on their own,
		 * so it's safe to remove the entry even if it's in use. */
#ifdef CONFIG_PROC_FS
		remove_proc_entry(c->pde->name, c->pde->parent);
#endif
		return;
	}
	write_unlock_bh(&clusterip_lock);
}