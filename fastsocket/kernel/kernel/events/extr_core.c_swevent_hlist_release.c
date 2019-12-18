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
struct swevent_htable {int /*<<< orphan*/  swevent_hlist; } ;
struct swevent_hlist {int /*<<< orphan*/  rcu_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct swevent_hlist* swevent_hlist_deref (struct swevent_htable*) ; 
 int /*<<< orphan*/  swevent_hlist_free ; 

__attribute__((used)) static void swevent_hlist_release(struct swevent_htable *swhash)
{
	struct swevent_hlist *hlist = swevent_hlist_deref(swhash);

	if (!hlist)
		return;

	rcu_assign_pointer(swhash->swevent_hlist, NULL);
	call_rcu(&hlist->rcu_head, swevent_hlist_free);
}