#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qdio_ssqd_desc {int dummy; } ;
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  sch_no; } ;
struct TYPE_3__ {TYPE_2__ schid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int qdio_setup_get_ssqd (int /*<<< orphan*/ *,TYPE_2__*,struct qdio_ssqd_desc*) ; 

int qdio_get_ssqd_desc(struct ccw_device *cdev,
		       struct qdio_ssqd_desc *data)
{

	if (!cdev || !cdev->private)
		return -EINVAL;

	DBF_EVENT("get ssqd:%4x", cdev->private->schid.sch_no);
	return qdio_setup_get_ssqd(NULL, &cdev->private->schid, data);
}