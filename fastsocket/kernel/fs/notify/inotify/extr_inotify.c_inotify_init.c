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
struct inotify_operations {int dummy; } ;
struct inotify_handle {int /*<<< orphan*/  count; struct inotify_operations const* in_ops; scalar_t__ last_wd; int /*<<< orphan*/  mutex; int /*<<< orphan*/  watches; int /*<<< orphan*/  idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct inotify_handle* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_inotify_handle (struct inotify_handle*) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 struct inotify_handle* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

struct inotify_handle *inotify_init(const struct inotify_operations *ops)
{
	struct inotify_handle *ih;

	ih = kmalloc(sizeof(struct inotify_handle), GFP_KERNEL);
	if (unlikely(!ih))
		return ERR_PTR(-ENOMEM);

	idr_init(&ih->idr);
	INIT_LIST_HEAD(&ih->watches);
	mutex_init(&ih->mutex);
	ih->last_wd = 0;
	ih->in_ops = ops;
	atomic_set(&ih->count, 0);
	get_inotify_handle(ih);

	return ih;
}