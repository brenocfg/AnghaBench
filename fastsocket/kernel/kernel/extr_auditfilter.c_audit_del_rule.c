#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct audit_watch {int dummy; } ;
struct audit_tree {int dummy; } ;
struct TYPE_3__ {scalar_t__ listnr; int /*<<< orphan*/  list; struct audit_tree* tree; struct audit_watch* watch; } ;
struct audit_entry {int /*<<< orphan*/  rcu; TYPE_1__ rule; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ AUDIT_FILTER_TYPE ; 
 scalar_t__ AUDIT_FILTER_USER ; 
 int ENOENT ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_filter_mutex ; 
 struct audit_entry* audit_find_rule (struct audit_entry*,struct list_head**) ; 
 int /*<<< orphan*/  audit_free_rule_rcu ; 
 int /*<<< orphan*/  audit_inotify_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_match_signal (struct audit_entry*) ; 
 int /*<<< orphan*/  audit_n_rules ; 
 int /*<<< orphan*/  audit_put_tree (struct audit_tree*) ; 
 int /*<<< orphan*/  audit_put_watch (struct audit_watch*) ; 
 int /*<<< orphan*/  audit_remove_tree_rule (TYPE_1__*) ; 
 int /*<<< orphan*/  audit_remove_watch_rule (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_signals ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inotify_list ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int audit_del_rule(struct audit_entry *entry)
{
	struct audit_entry  *e;
	struct audit_watch *watch = entry->rule.watch;
	struct audit_tree *tree = entry->rule.tree;
	struct list_head *list;
	LIST_HEAD(inotify_list);
	int ret = 0;
#ifdef CONFIG_AUDITSYSCALL
	int dont_count = 0;

	/* If either of these, don't count towards total */
	if (entry->rule.listnr == AUDIT_FILTER_USER ||
		entry->rule.listnr == AUDIT_FILTER_TYPE)
		dont_count = 1;
#endif

	mutex_lock(&audit_filter_mutex);
	e = audit_find_rule(entry, &list);
	if (!e) {
		mutex_unlock(&audit_filter_mutex);
		ret = -ENOENT;
		goto out;
	}

	if (e->rule.watch)
		audit_remove_watch_rule(&e->rule, &inotify_list);

	if (e->rule.tree)
		audit_remove_tree_rule(&e->rule);

	list_del_rcu(&e->list);
	list_del(&e->rule.list);
	call_rcu(&e->rcu, audit_free_rule_rcu);

#ifdef CONFIG_AUDITSYSCALL
	if (!dont_count)
		audit_n_rules--;

	if (!audit_match_signal(entry))
		audit_signals--;
#endif
	mutex_unlock(&audit_filter_mutex);

	if (!list_empty(&inotify_list))
		audit_inotify_unregister(&inotify_list);

out:
	if (watch)
		audit_put_watch(watch); /* match initial get */
	if (tree)
		audit_put_tree(tree);	/* that's the temporary one */

	return ret;
}