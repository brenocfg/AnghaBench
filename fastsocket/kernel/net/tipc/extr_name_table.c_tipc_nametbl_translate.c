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
typedef  int /*<<< orphan*/  u32 ;
struct sub_seq {struct publication* zone_list; struct publication* cluster_list; struct publication* node_list; } ;
struct publication {struct publication* zone_list_next; struct publication* cluster_list_next; struct publication* node_list_next; int /*<<< orphan*/  node; int /*<<< orphan*/  ref; } ;
struct name_seq {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ in_own_cluster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_scope (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 struct sub_seq* nameseq_find_subseq (struct name_seq*,int /*<<< orphan*/ ) ; 
 struct name_seq* nametbl_find_seq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_nametbl_lock ; 
 int /*<<< orphan*/  tipc_own_addr ; 
 scalar_t__ unlikely (int) ; 

u32 tipc_nametbl_translate(u32 type, u32 instance, u32 *destnode)
{
	struct sub_seq *sseq;
	struct publication *publ = NULL;
	struct name_seq *seq;
	u32 ref;

	if (!in_scope(*destnode, tipc_own_addr))
		return 0;

	read_lock_bh(&tipc_nametbl_lock);
	seq = nametbl_find_seq(type);
	if (unlikely(!seq))
		goto not_found;
	sseq = nameseq_find_subseq(seq, instance);
	if (unlikely(!sseq))
		goto not_found;
	spin_lock_bh(&seq->lock);

	/* Closest-First Algorithm: */
	if (likely(!*destnode)) {
		publ = sseq->node_list;
		if (publ) {
			sseq->node_list = publ->node_list_next;
found:
			ref = publ->ref;
			*destnode = publ->node;
			spin_unlock_bh(&seq->lock);
			read_unlock_bh(&tipc_nametbl_lock);
			return ref;
		}
		publ = sseq->cluster_list;
		if (publ) {
			sseq->cluster_list = publ->cluster_list_next;
			goto found;
		}
		publ = sseq->zone_list;
		if (publ) {
			sseq->zone_list = publ->zone_list_next;
			goto found;
		}
	}

	/* Round-Robin Algorithm: */
	else if (*destnode == tipc_own_addr) {
		publ = sseq->node_list;
		if (publ) {
			sseq->node_list = publ->node_list_next;
			goto found;
		}
	} else if (in_own_cluster(*destnode)) {
		publ = sseq->cluster_list;
		if (publ) {
			sseq->cluster_list = publ->cluster_list_next;
			goto found;
		}
	} else {
		publ = sseq->zone_list;
		if (publ) {
			sseq->zone_list = publ->zone_list_next;
			goto found;
		}
	}
	spin_unlock_bh(&seq->lock);
not_found:
	*destnode = 0;
	read_unlock_bh(&tipc_nametbl_lock);
	return 0;
}