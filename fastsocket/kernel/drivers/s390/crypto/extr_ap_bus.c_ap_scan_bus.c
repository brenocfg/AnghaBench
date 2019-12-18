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
struct work_struct {int dummy; } ;
struct device {int /*<<< orphan*/  kobj; int /*<<< orphan*/  release; int /*<<< orphan*/  parent; int /*<<< orphan*/ * bus; } ;
struct ap_device {int unregistered; int queue_depth; int device_type; unsigned int functions; struct device device; int /*<<< orphan*/  lock; scalar_t__ qid; int /*<<< orphan*/  timeout; int /*<<< orphan*/  list; int /*<<< orphan*/  requestq; int /*<<< orphan*/  pendingq; } ;
typedef  scalar_t__ ap_qid_t ;

/* Variables and functions */
 int AP_DEVICES ; 
 scalar_t__ AP_MKQID (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AP_QID_DEVICE (scalar_t__) ; 
 int /*<<< orphan*/  AP_RESET_TIMEOUT ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __ap_scan_bus ; 
 int /*<<< orphan*/  ap_bus_type ; 
 int /*<<< orphan*/  ap_dev_attr_group ; 
 int /*<<< orphan*/  ap_device_release ; 
 int /*<<< orphan*/  ap_domain_index ; 
 int ap_init_queue (scalar_t__) ; 
 int /*<<< orphan*/  ap_probe_device_type (struct ap_device*) ; 
 int /*<<< orphan*/  ap_query_configuration () ; 
 int ap_query_functions (scalar_t__,unsigned int*) ; 
 int ap_query_queue (scalar_t__,int*,int*) ; 
 int /*<<< orphan*/  ap_request_timeout ; 
 int /*<<< orphan*/  ap_root_device ; 
 scalar_t__ ap_select_domain () ; 
 scalar_t__ ap_test_config_card_id (int) ; 
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ dev_set_name (struct device*,char*,int /*<<< orphan*/ ) ; 
 int device_register (struct device*) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  kfree (struct ap_device*) ; 
 struct ap_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ap_device* to_ap_dev (struct device*) ; 

__attribute__((used)) static void ap_scan_bus(struct work_struct *unused)
{
	struct ap_device *ap_dev;
	struct device *dev;
	ap_qid_t qid;
	int queue_depth, device_type;
	unsigned int device_functions;
	int rc, i;

	ap_query_configuration();
	if (ap_select_domain() != 0) {
		return;
	}
	for (i = 0; i < AP_DEVICES; i++) {
		qid = AP_MKQID(i, ap_domain_index);
		dev = bus_find_device(&ap_bus_type, NULL,
				      (void *)(unsigned long)qid,
				      __ap_scan_bus);
		if (ap_test_config_card_id(i))
			rc = ap_query_queue(qid, &queue_depth, &device_type);
		else
			rc = -ENODEV;
		if (dev) {
			if (rc == -EBUSY) {
				set_current_state(TASK_UNINTERRUPTIBLE);
				schedule_timeout(AP_RESET_TIMEOUT);
				rc = ap_query_queue(qid, &queue_depth,
						    &device_type);
			}
			ap_dev = to_ap_dev(dev);
			spin_lock_bh(&ap_dev->lock);
			if (rc || ap_dev->unregistered) {
				spin_unlock_bh(&ap_dev->lock);
				if (ap_dev->unregistered)
					i--;
				device_unregister(dev);
				put_device(dev);
				continue;
			}
			spin_unlock_bh(&ap_dev->lock);
			put_device(dev);
			continue;
		}
		if (rc)
			continue;
		rc = ap_init_queue(qid);
		if (rc)
			continue;
		ap_dev = kzalloc(sizeof(*ap_dev), GFP_KERNEL);
		if (!ap_dev)
			break;
		ap_dev->qid = qid;
		ap_dev->queue_depth = queue_depth;
		ap_dev->unregistered = 1;
		spin_lock_init(&ap_dev->lock);
		INIT_LIST_HEAD(&ap_dev->pendingq);
		INIT_LIST_HEAD(&ap_dev->requestq);
		INIT_LIST_HEAD(&ap_dev->list);
		setup_timer(&ap_dev->timeout, ap_request_timeout,
			    (unsigned long) ap_dev);
		switch (device_type) {
		case 0:
			/* device type probing for old cards */
			if (ap_probe_device_type(ap_dev)) {
				kfree(ap_dev);
				continue;
			}
			break;
		default:
			ap_dev->device_type = device_type;
		}

		rc = ap_query_functions(qid, &device_functions);
		if (!rc)
			ap_dev->functions = device_functions;
		else
			ap_dev->functions = 0u;

		ap_dev->device.bus = &ap_bus_type;
		ap_dev->device.parent = ap_root_device;
		if (dev_set_name(&ap_dev->device, "card%02x",
				 AP_QID_DEVICE(ap_dev->qid))) {
			kfree(ap_dev);
			continue;
		}
		ap_dev->device.release = ap_device_release;
		rc = device_register(&ap_dev->device);
		if (rc) {
			put_device(&ap_dev->device);
			continue;
		}
		/* Add device attributes. */
		rc = sysfs_create_group(&ap_dev->device.kobj,
					&ap_dev_attr_group);
		if (!rc) {
			spin_lock_bh(&ap_dev->lock);
			ap_dev->unregistered = 0;
			spin_unlock_bh(&ap_dev->lock);
		} else
			device_unregister(&ap_dev->device);
	}
}