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
struct fsnotify_ops {int dummy; } ;
struct fsnotify_group {int on_group_list; unsigned int group_num; int /*<<< orphan*/  num_marks; int /*<<< orphan*/  group_list; struct fsnotify_ops const* ops; int /*<<< orphan*/  mark_entries; int /*<<< orphan*/  mark_lock; int /*<<< orphan*/  max_events; scalar_t__ q_len; int /*<<< orphan*/  notification_waitq; int /*<<< orphan*/  notification_list; int /*<<< orphan*/  notification_mutex; scalar_t__ mask; int /*<<< orphan*/  refcnt; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct fsnotify_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct fsnotify_group* fsnotify_find_group (unsigned int,scalar_t__,struct fsnotify_ops const*) ; 
 int /*<<< orphan*/  fsnotify_groups ; 
 int /*<<< orphan*/  fsnotify_grp_mutex ; 
 int /*<<< orphan*/  fsnotify_put_group (struct fsnotify_group*) ; 
 int /*<<< orphan*/  fsnotify_recalc_global_mask () ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct fsnotify_group* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct fsnotify_group *fsnotify_obtain_group(unsigned int group_num, __u32 mask,
					     const struct fsnotify_ops *ops)
{
	struct fsnotify_group *group, *tgroup;

	/* very low use, simpler locking if we just always alloc */
	group = kmalloc(sizeof(struct fsnotify_group), GFP_KERNEL);
	if (!group)
		return ERR_PTR(-ENOMEM);

	atomic_set(&group->refcnt, 1);

	group->on_group_list = 0;
	group->group_num = group_num;
	group->mask = mask;

	mutex_init(&group->notification_mutex);
	INIT_LIST_HEAD(&group->notification_list);
	init_waitqueue_head(&group->notification_waitq);
	group->q_len = 0;
	group->max_events = UINT_MAX;

	spin_lock_init(&group->mark_lock);
	atomic_set(&group->num_marks, 0);
	INIT_LIST_HEAD(&group->mark_entries);

	group->ops = ops;

	mutex_lock(&fsnotify_grp_mutex);
	tgroup = fsnotify_find_group(group_num, mask, ops);
	if (tgroup) {
		/* group already exists */
		mutex_unlock(&fsnotify_grp_mutex);
		/* destroy the new one we made */
		fsnotify_put_group(group);
		return tgroup;
	}

	/* group not found, add a new one */
	list_add_rcu(&group->group_list, &fsnotify_groups);
	group->on_group_list = 1;
	/* being on the fsnotify_groups list holds one num_marks */
	atomic_inc(&group->num_marks);

	mutex_unlock(&fsnotify_grp_mutex);

	if (mask)
		fsnotify_recalc_global_mask();

	return group;
}