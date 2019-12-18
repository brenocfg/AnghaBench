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
struct cxgbi_device {int /*<<< orphan*/  list_head; TYPE_1__** ports; scalar_t__ nports; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int CXGBI_DBG_DEV ; 
 int /*<<< orphan*/  cdev_mutex ; 
 int /*<<< orphan*/  cxgbi_device_destroy (struct cxgbi_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_device*,scalar_t__,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void cxgbi_device_unregister(struct cxgbi_device *cdev)
{
	log_debug(1 << CXGBI_DBG_DEV,
		"cdev 0x%p, p# %u,%s.\n",
		cdev, cdev->nports, cdev->nports ? cdev->ports[0]->name : "");
	mutex_lock(&cdev_mutex);
	list_del(&cdev->list_head);
	mutex_unlock(&cdev_mutex);
	cxgbi_device_destroy(cdev);
}