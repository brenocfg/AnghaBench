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
struct TYPE_2__ {int /*<<< orphan*/  ref; } ;
struct request_queue {TYPE_1__ bsg_dev; } ;
struct bsg_device {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; int /*<<< orphan*/  dev_list; int /*<<< orphan*/  ref_count; struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSG_F_BLOCK ; 
 int atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_put_queue (struct request_queue*) ; 
 int bsg_complete_all_commands (struct bsg_device*) ; 
 int /*<<< orphan*/  bsg_kref_release_function ; 
 int /*<<< orphan*/  bsg_mutex ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bsg_device*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bsg_put_device(struct bsg_device *bd)
{
	int ret = 0, do_free;
	struct request_queue *q = bd->queue;

	mutex_lock(&bsg_mutex);

	do_free = atomic_dec_and_test(&bd->ref_count);
	if (!do_free) {
		mutex_unlock(&bsg_mutex);
		goto out;
	}

	hlist_del(&bd->dev_list);
	mutex_unlock(&bsg_mutex);

	dprintk("%s: tearing down\n", bd->name);

	/*
	 * close can always block
	 */
	set_bit(BSG_F_BLOCK, &bd->flags);

	/*
	 * correct error detection baddies here again. it's the responsibility
	 * of the app to properly reap commands before close() if it wants
	 * fool-proof error detection
	 */
	ret = bsg_complete_all_commands(bd);

	kfree(bd);
out:
	kref_put(&q->bsg_dev.ref, bsg_kref_release_function);
	if (do_free)
		blk_put_queue(q);
	return ret;
}