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
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;
struct adsp_device {char const* name; struct device* device; TYPE_1__ cdev; int /*<<< orphan*/  event_queue_lock; int /*<<< orphan*/  event_queue; int /*<<< orphan*/  event_wait; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adsp_class ; 
 int /*<<< orphan*/  adsp_fops ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct device* device_create (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adsp_create(struct adsp_device *adev, const char *name,
			struct device *parent, dev_t devt)
{
	struct device *dev;
	int rc;

	dev = device_create(adsp_class, parent, devt, "%s", name);
	if (IS_ERR(dev))
		return;

	init_waitqueue_head(&adev->event_wait);
	INIT_LIST_HEAD(&adev->event_queue);
	spin_lock_init(&adev->event_queue_lock);

	cdev_init(&adev->cdev, &adsp_fops);
	adev->cdev.owner = THIS_MODULE;

	rc = cdev_add(&adev->cdev, devt, 1);
	if (rc < 0) {
		device_destroy(adsp_class, devt);
	} else {
		adev->device = dev;
		adev->name = name;
	}
}