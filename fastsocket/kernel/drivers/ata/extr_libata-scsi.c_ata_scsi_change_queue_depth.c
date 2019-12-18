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
struct scsi_device {int /*<<< orphan*/  host; } ;
struct ata_port {int dummy; } ;

/* Variables and functions */
 int __ata_change_queue_depth (struct ata_port*,struct scsi_device*,int,int) ; 
 struct ata_port* ata_shost_to_port (int /*<<< orphan*/ ) ; 

int ata_scsi_change_queue_depth(struct scsi_device *sdev, int queue_depth,
				int reason)
{
	struct ata_port *ap = ata_shost_to_port(sdev->host);

	return __ata_change_queue_depth(ap, sdev, queue_depth, reason);
}