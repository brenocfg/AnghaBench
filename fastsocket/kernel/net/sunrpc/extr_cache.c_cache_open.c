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
struct inode {int dummy; } ;
struct file {int f_mode; struct cache_reader* private_data; } ;
struct TYPE_2__ {int reader; int /*<<< orphan*/  list; } ;
struct cache_reader {TYPE_1__ q; scalar_t__ offset; } ;
struct cache_detail {int /*<<< orphan*/  queue; int /*<<< orphan*/  readers; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOMEM ; 
 int FMODE_READ ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct cache_reader* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  queue_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cache_open(struct inode *inode, struct file *filp,
		      struct cache_detail *cd)
{
	struct cache_reader *rp = NULL;

	if (!cd || !try_module_get(cd->owner))
		return -EACCES;
	nonseekable_open(inode, filp);
	if (filp->f_mode & FMODE_READ) {
		rp = kmalloc(sizeof(*rp), GFP_KERNEL);
		if (!rp)
			return -ENOMEM;
		rp->offset = 0;
		rp->q.reader = 1;
		atomic_inc(&cd->readers);
		spin_lock(&queue_lock);
		list_add(&rp->q.list, &cd->queue);
		spin_unlock(&queue_lock);
	}
	filp->private_data = rp;
	return 0;
}