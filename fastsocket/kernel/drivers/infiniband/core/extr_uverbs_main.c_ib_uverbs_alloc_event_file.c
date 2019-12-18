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
struct ib_uverbs_file {int dummy; } ;
struct ib_uverbs_event_file {int is_async; scalar_t__ is_closed; int /*<<< orphan*/ * async_queue; struct ib_uverbs_file* uverbs_file; int /*<<< orphan*/  poll_wait; int /*<<< orphan*/  event_list; int /*<<< orphan*/  lock; int /*<<< orphan*/  ref; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int ENFILE ; 
 int ENOMEM ; 
 struct file* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 struct file* anon_inode_getfile (char*,int /*<<< orphan*/ *,struct ib_uverbs_event_file*,int /*<<< orphan*/ ) ; 
 int get_unused_fd () ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_uverbs_event_file*) ; 
 struct ib_uverbs_event_file* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uverbs_event_fops ; 

struct file *ib_uverbs_alloc_event_file(struct ib_uverbs_file *uverbs_file,
					int is_async, int *fd)
{
	struct ib_uverbs_event_file *ev_file;
	struct file *filp;
	int ret;

	ev_file = kmalloc(sizeof *ev_file, GFP_KERNEL);
	if (!ev_file)
		return ERR_PTR(-ENOMEM);

	kref_init(&ev_file->ref);
	spin_lock_init(&ev_file->lock);
	INIT_LIST_HEAD(&ev_file->event_list);
	init_waitqueue_head(&ev_file->poll_wait);
	ev_file->uverbs_file = uverbs_file;
	ev_file->async_queue = NULL;
	ev_file->is_async    = is_async;
	ev_file->is_closed   = 0;

	*fd = get_unused_fd();
	if (*fd < 0) {
		ret = *fd;
		goto err;
	}

	filp = anon_inode_getfile("[uverbs-event]", &uverbs_event_fops,
				  ev_file, O_RDONLY);
	if (!filp) {
		ret = -ENFILE;
		goto err_fd;
	}

	return filp;

err_fd:
	put_unused_fd(*fd);

err:
	kfree(ev_file);
	return ERR_PTR(ret);
}