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
struct per_user_data {int /*<<< orphan*/  ring_cons_mutex; int /*<<< orphan*/  bind_mutex; struct per_user_data* name; int /*<<< orphan*/ * ring; int /*<<< orphan*/  evtchn_wait; } ;
struct inode {int dummy; } ;
struct file {struct per_user_data* private_data; } ;
typedef  int /*<<< orphan*/  evtchn_port_t ;
struct TYPE_2__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct per_user_data* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct per_user_data*) ; 
 struct per_user_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int evtchn_open(struct inode *inode, struct file *filp)
{
	struct per_user_data *u;

	u = kzalloc(sizeof(*u), GFP_KERNEL);
	if (u == NULL)
		return -ENOMEM;

	u->name = kasprintf(GFP_KERNEL, "evtchn:%s", current->comm);
	if (u->name == NULL) {
		kfree(u);
		return -ENOMEM;
	}

	init_waitqueue_head(&u->evtchn_wait);

	u->ring = (evtchn_port_t *)__get_free_page(GFP_KERNEL);
	if (u->ring == NULL) {
		kfree(u->name);
		kfree(u);
		return -ENOMEM;
	}

	mutex_init(&u->bind_mutex);
	mutex_init(&u->ring_cons_mutex);

	filp->private_data = u;

	return 0;
}