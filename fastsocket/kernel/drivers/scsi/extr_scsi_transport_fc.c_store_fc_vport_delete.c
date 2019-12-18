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
struct fc_vport {int flags; int /*<<< orphan*/  vport_delete_work; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EBUSY ; 
 int FC_VPORT_CREATING ; 
 int FC_VPORT_DEL ; 
 int FC_VPORT_DELETING ; 
 int /*<<< orphan*/  fc_queue_work (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct fc_vport* transport_class_to_vport (struct device*) ; 
 struct Scsi_Host* vport_to_shost (struct fc_vport*) ; 

__attribute__((used)) static ssize_t
store_fc_vport_delete(struct device *dev, struct device_attribute *attr,
		      const char *buf, size_t count)
{
	struct fc_vport *vport = transport_class_to_vport(dev);
	struct Scsi_Host *shost = vport_to_shost(vport);
	unsigned long flags;

	spin_lock_irqsave(shost->host_lock, flags);
	if (vport->flags & (FC_VPORT_DEL | FC_VPORT_CREATING)) {
		spin_unlock_irqrestore(shost->host_lock, flags);
		return -EBUSY;
	}
	vport->flags |= FC_VPORT_DELETING;
	spin_unlock_irqrestore(shost->host_lock, flags);

	fc_queue_work(shost, &vport->vport_delete_work);
	return count;
}