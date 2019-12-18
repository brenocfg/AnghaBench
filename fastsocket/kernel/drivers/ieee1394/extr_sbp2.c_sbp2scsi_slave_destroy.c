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
struct scsi_device {TYPE_1__* host; } ;
struct sbp2_lu {int /*<<< orphan*/ * sdev; } ;
struct TYPE_2__ {scalar_t__* hostdata; } ;

/* Variables and functions */

__attribute__((used)) static void sbp2scsi_slave_destroy(struct scsi_device *sdev)
{
	((struct sbp2_lu *)sdev->host->hostdata[0])->sdev = NULL;
	return;
}