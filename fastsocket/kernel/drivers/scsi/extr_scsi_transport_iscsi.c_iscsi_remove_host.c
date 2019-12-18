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
struct transport_container {int dummy; } ;
struct iscsi_cls_host {scalar_t__ bsg_q; } ;
struct device {int dummy; } ;
struct Scsi_Host {struct iscsi_cls_host* shost_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (scalar_t__) ; 
 int /*<<< orphan*/  bsg_remove_queue (scalar_t__) ; 
 struct Scsi_Host* dev_to_shost (struct device*) ; 

__attribute__((used)) static int iscsi_remove_host(struct transport_container *tc,
			     struct device *dev, struct device *cdev)
{
	struct Scsi_Host *shost = dev_to_shost(dev);
	struct iscsi_cls_host *ihost = shost->shost_data;

	if (ihost->bsg_q) {
		bsg_remove_queue(ihost->bsg_q);
		blk_cleanup_queue(ihost->bsg_q);
	}
	return 0;
}