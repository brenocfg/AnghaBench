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
struct rpc_sequence {int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; } ;
struct nfs_seqid {int /*<<< orphan*/  list; TYPE_1__* sequence; } ;
struct TYPE_2__ {struct rpc_sequence* sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfs_release_seqid(struct nfs_seqid *seqid)
{
	if (!list_empty(&seqid->list)) {
		struct rpc_sequence *sequence = seqid->sequence->sequence;

		spin_lock(&sequence->lock);
		list_del_init(&seqid->list);
		spin_unlock(&sequence->lock);
		rpc_wake_up(&sequence->wait);
	}
}