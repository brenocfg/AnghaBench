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
struct mon_bus {int /*<<< orphan*/  ref; scalar_t__ bin_inited; scalar_t__ text_inited; int /*<<< orphan*/  bus_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mon_bin_del (struct mon_bus*) ; 
 int /*<<< orphan*/  mon_bus_drop ; 
 int /*<<< orphan*/  mon_dissolve (struct mon_bus*,struct usb_bus*) ; 
 int /*<<< orphan*/  mon_lock ; 
 int /*<<< orphan*/  mon_text_del (struct mon_bus*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mon_bus_remove(struct usb_bus *ubus)
{
	struct mon_bus *mbus = ubus->mon_bus;

	mutex_lock(&mon_lock);
	list_del(&mbus->bus_link);
	if (mbus->text_inited)
		mon_text_del(mbus);
	if (mbus->bin_inited)
		mon_bin_del(mbus);

	mon_dissolve(mbus, ubus);
	kref_put(&mbus->ref, mon_bus_drop);
	mutex_unlock(&mon_lock);
}