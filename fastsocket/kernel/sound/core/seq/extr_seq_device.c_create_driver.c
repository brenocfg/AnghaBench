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
struct ops_list {int used; int /*<<< orphan*/  list; int /*<<< orphan*/  dev_list; int /*<<< orphan*/  driver; int /*<<< orphan*/  reg_mutex; int /*<<< orphan*/  id; } ;
struct lock_class_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_EMPTY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ops_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,struct lock_class_key*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_ops ; 
 int /*<<< orphan*/  ops_mutex ; 
 int /*<<< orphan*/  opslist ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct ops_list * create_driver(char *id)
{
	struct ops_list *ops;

	ops = kzalloc(sizeof(*ops), GFP_KERNEL);
	if (ops == NULL)
		return ops;

	/* set up driver entry */
	strlcpy(ops->id, id, sizeof(ops->id));
	mutex_init(&ops->reg_mutex);
	/*
	 * The ->reg_mutex locking rules are per-driver, so we create
	 * separate per-driver lock classes:
	 */
	lockdep_set_class(&ops->reg_mutex, (struct lock_class_key *)id);

	ops->driver = DRIVER_EMPTY;
	INIT_LIST_HEAD(&ops->dev_list);
	/* lock this instance */
	ops->used = 1;

	/* register driver entry */
	mutex_lock(&ops_mutex);
	list_add_tail(&ops->list, &opslist);
	num_ops++;
	mutex_unlock(&ops_mutex);

	return ops;
}