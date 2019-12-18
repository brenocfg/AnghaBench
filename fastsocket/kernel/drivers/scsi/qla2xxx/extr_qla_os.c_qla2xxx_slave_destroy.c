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
struct scsi_device {int /*<<< orphan*/ * hostdata; } ;

/* Variables and functions */

__attribute__((used)) static void
qla2xxx_slave_destroy(struct scsi_device *sdev)
{
	sdev->hostdata = NULL;
}