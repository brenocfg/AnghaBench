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
struct smscore_device_t {int /*<<< orphan*/  device; } ;
struct smscore_device_notifyee_t {int (* hotplug ) (struct smscore_device_t*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  entry; } ;
struct list_head {struct list_head* next; } ;
typedef  int (* hotplug_t ) (struct smscore_device_t*,int /*<<< orphan*/ ,int) ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct list_head g_smscore_devices ; 
 int /*<<< orphan*/  g_smscore_deviceslock ; 
 int /*<<< orphan*/  g_smscore_notifyees ; 
 int /*<<< orphan*/  kfree (struct smscore_device_notifyee_t*) ; 
 struct smscore_device_notifyee_t* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int smscore_register_hotplug(hotplug_t hotplug)
{
	struct smscore_device_notifyee_t *notifyee;
	struct list_head *next, *first;
	int rc = 0;

	kmutex_lock(&g_smscore_deviceslock);

	notifyee = kmalloc(sizeof(struct smscore_device_notifyee_t),
			   GFP_KERNEL);
	if (notifyee) {
		/* now notify callback about existing devices */
		first = &g_smscore_devices;
		for (next = first->next;
		     next != first && !rc;
		     next = next->next) {
			struct smscore_device_t *coredev =
				(struct smscore_device_t *) next;
			rc = hotplug(coredev, coredev->device, 1);
		}

		if (rc >= 0) {
			notifyee->hotplug = hotplug;
			list_add(&notifyee->entry, &g_smscore_notifyees);
		} else
			kfree(notifyee);
	} else
		rc = -ENOMEM;

	kmutex_unlock(&g_smscore_deviceslock);

	return rc;
}