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
struct xt_hashlimit_htable {int /*<<< orphan*/  node; int /*<<< orphan*/  use; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashlimit_lock ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htable_destroy (struct xt_hashlimit_htable*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void htable_put(struct xt_hashlimit_htable *hinfo)
{
	if (atomic_dec_and_test(&hinfo->use)) {
		spin_lock_bh(&hashlimit_lock);
		hlist_del(&hinfo->node);
		spin_unlock_bh(&hashlimit_lock);
		htable_destroy(hinfo);
	}
}