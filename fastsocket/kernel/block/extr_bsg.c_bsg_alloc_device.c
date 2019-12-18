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
struct bsg_device {int /*<<< orphan*/  wq_done; int /*<<< orphan*/  wq_free; int /*<<< orphan*/  dev_list; int /*<<< orphan*/  done_list; int /*<<< orphan*/  busy_list; int /*<<< orphan*/  max_queue; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSG_DEFAULT_CMDS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct bsg_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct bsg_device *bsg_alloc_device(void)
{
	struct bsg_device *bd;

	bd = kzalloc(sizeof(struct bsg_device), GFP_KERNEL);
	if (unlikely(!bd))
		return NULL;

	spin_lock_init(&bd->lock);

	bd->max_queue = BSG_DEFAULT_CMDS;

	INIT_LIST_HEAD(&bd->busy_list);
	INIT_LIST_HEAD(&bd->done_list);
	INIT_HLIST_NODE(&bd->dev_list);

	init_waitqueue_head(&bd->wq_free);
	init_waitqueue_head(&bd->wq_done);
	return bd;
}