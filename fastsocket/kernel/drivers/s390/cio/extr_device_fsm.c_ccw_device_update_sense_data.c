#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dev_model; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  cu_model; int /*<<< orphan*/  cu_type; } ;
struct ccw_device {TYPE_1__* private; TYPE_3__ id; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev_model; int /*<<< orphan*/  dev_type; int /*<<< orphan*/  cu_model; int /*<<< orphan*/  cu_type; } ;
struct TYPE_4__ {TYPE_2__ senseid; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void ccw_device_update_sense_data(struct ccw_device *cdev)
{
	memset(&cdev->id, 0, sizeof(cdev->id));
	cdev->id.cu_type   = cdev->private->senseid.cu_type;
	cdev->id.cu_model  = cdev->private->senseid.cu_model;
	cdev->id.dev_type  = cdev->private->senseid.dev_type;
	cdev->id.dev_model = cdev->private->senseid.dev_model;
}