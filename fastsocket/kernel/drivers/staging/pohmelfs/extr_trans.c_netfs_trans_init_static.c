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
struct netfs_trans {int page_num; int total_size; int /*<<< orphan*/  dst_list; int /*<<< orphan*/  dst_lock; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netfs_trans_init_static(struct netfs_trans *t, int num, int size)
{
	t->page_num = num;
	t->total_size = size;
	atomic_set(&t->refcnt, 1);

	spin_lock_init(&t->dst_lock);
	INIT_LIST_HEAD(&t->dst_list);
}