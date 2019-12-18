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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct subscription {int /*<<< orphan*/  nameseq_list; TYPE_1__ seq; } ;
struct name_seq {scalar_t__ first_free; struct name_seq* sseqs; int /*<<< orphan*/  ns_list; int /*<<< orphan*/  subscriptions; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct name_seq*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct name_seq* nametbl_find_seq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_nametbl_lock ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void tipc_nametbl_unsubscribe(struct subscription *s)
{
	struct name_seq *seq;

	write_lock_bh(&tipc_nametbl_lock);
	seq = nametbl_find_seq(s->seq.type);
	if (seq != NULL){
		spin_lock_bh(&seq->lock);
		list_del_init(&s->nameseq_list);
		spin_unlock_bh(&seq->lock);
		if ((seq->first_free == 0) && list_empty(&seq->subscriptions)) {
			hlist_del_init(&seq->ns_list);
			kfree(seq->sseqs);
			kfree(seq);
		}
	}
	write_unlock_bh(&tipc_nametbl_lock);
}