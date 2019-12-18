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
struct usb_bus {struct mon_bus* mon_bus; } ;
struct mon_bus {int /*<<< orphan*/  bus_link; int /*<<< orphan*/  bin_inited; int /*<<< orphan*/  text_inited; struct usb_bus* u_bus; int /*<<< orphan*/  r_list; int /*<<< orphan*/  lock; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct mon_bus* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mon_bin_add (struct mon_bus*,struct usb_bus*) ; 
 int /*<<< orphan*/  mon_buses ; 
 int /*<<< orphan*/  mon_lock ; 
 int /*<<< orphan*/  mon_text_add (struct mon_bus*,struct usb_bus*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mon_bus_init(struct usb_bus *ubus)
{
	struct mon_bus *mbus;

	if ((mbus = kzalloc(sizeof(struct mon_bus), GFP_KERNEL)) == NULL)
		goto err_alloc;
	kref_init(&mbus->ref);
	spin_lock_init(&mbus->lock);
	INIT_LIST_HEAD(&mbus->r_list);

	/*
	 * We don't need to take a reference to ubus, because we receive
	 * a notification if the bus is about to be removed.
	 */
	mbus->u_bus = ubus;
	ubus->mon_bus = mbus;

	mbus->text_inited = mon_text_add(mbus, ubus);
	mbus->bin_inited = mon_bin_add(mbus, ubus);

	mutex_lock(&mon_lock);
	list_add_tail(&mbus->bus_link, &mon_buses);
	mutex_unlock(&mon_lock);
	return;

err_alloc:
	return;
}