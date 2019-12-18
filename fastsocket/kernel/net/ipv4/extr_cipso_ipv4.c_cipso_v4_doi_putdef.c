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
struct cipso_v4_doi {int /*<<< orphan*/  rcu; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cipso_v4_cache_invalidate () ; 
 int /*<<< orphan*/  cipso_v4_doi_free_rcu ; 
 int /*<<< orphan*/  cipso_v4_doi_list_lock ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void cipso_v4_doi_putdef(struct cipso_v4_doi *doi_def)
{
	if (doi_def == NULL)
		return;

	if (!atomic_dec_and_test(&doi_def->refcount))
		return;
	spin_lock(&cipso_v4_doi_list_lock);
	list_del_rcu(&doi_def->list);
	spin_unlock(&cipso_v4_doi_list_lock);

	cipso_v4_cache_invalidate();
	call_rcu(&doi_def->rcu, cipso_v4_doi_free_rcu);
}