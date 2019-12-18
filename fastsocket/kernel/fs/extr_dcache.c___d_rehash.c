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
struct hlist_head {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_hash; int /*<<< orphan*/  d_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_UNHASHED ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,struct hlist_head*) ; 

__attribute__((used)) static void __d_rehash(struct dentry * entry, struct hlist_head *list)
{

 	entry->d_flags &= ~DCACHE_UNHASHED;
 	hlist_add_head_rcu(&entry->d_hash, list);
}