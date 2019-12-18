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
struct ccw_device {TYPE_2__* private; } ;
struct TYPE_6__ {int cu_type; } ;
struct TYPE_4__ {scalar_t__ esid; } ;
struct TYPE_5__ {TYPE_3__ senseid; TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snsid_init(struct ccw_device *cdev)
{
	cdev->private->flags.esid = 0;
	memset(&cdev->private->senseid, 0, sizeof(cdev->private->senseid));
	cdev->private->senseid.cu_type = 0xffff;
}