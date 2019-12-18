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
struct scsi_device {int tagged_supported; TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  can_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_activate_tcq (struct scsi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
stex_slave_alloc(struct scsi_device *sdev)
{
	/* Cheat: usually extracted from Inquiry data */
	sdev->tagged_supported = 1;

	scsi_activate_tcq(sdev, sdev->host->can_queue);

	return 0;
}