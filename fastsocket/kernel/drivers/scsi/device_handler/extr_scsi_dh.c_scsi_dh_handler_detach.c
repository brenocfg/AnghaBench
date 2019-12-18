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
struct scsi_device_handler {scalar_t__ detach; } ;
struct scsi_device {TYPE_1__* scsi_dh_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  kref; struct scsi_device_handler* scsi_dh; } ;

/* Variables and functions */
 int /*<<< orphan*/  __detach_handler ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scsi_dh_handler_detach(struct scsi_device *sdev,
				   struct scsi_device_handler *scsi_dh)
{
	if (!sdev->scsi_dh_data)
		return;

	if (scsi_dh && scsi_dh != sdev->scsi_dh_data->scsi_dh)
		return;

	if (!scsi_dh)
		scsi_dh = sdev->scsi_dh_data->scsi_dh;

	if (scsi_dh && scsi_dh->detach)
		kref_put(&sdev->scsi_dh_data->kref, __detach_handler);
}