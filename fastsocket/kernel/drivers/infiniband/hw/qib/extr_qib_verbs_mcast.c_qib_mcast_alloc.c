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
typedef  union ib_gid {int dummy; } ib_gid ;
struct qib_mcast {scalar_t__ n_attached; int /*<<< orphan*/  refcount; int /*<<< orphan*/  wait; int /*<<< orphan*/  qp_list; union ib_gid mgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct qib_mcast* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct qib_mcast *qib_mcast_alloc(union ib_gid *mgid)
{
	struct qib_mcast *mcast;

	mcast = kmalloc(sizeof *mcast, GFP_KERNEL);
	if (!mcast)
		goto bail;

	mcast->mgid = *mgid;
	INIT_LIST_HEAD(&mcast->qp_list);
	init_waitqueue_head(&mcast->wait);
	atomic_set(&mcast->refcount, 0);
	mcast->n_attached = 0;

bail:
	return mcast;
}