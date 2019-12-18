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
struct qdio_irq {int dummy; } ;
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_2__ {struct qdio_irq* qdio_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  qdio_free (struct ccw_device*) ; 
 int qdio_shutdown (struct ccw_device*,int) ; 

int qdio_cleanup(struct ccw_device *cdev, int how)
{
	struct qdio_irq *irq_ptr = cdev->private->qdio_data;
	int rc;

	if (!irq_ptr)
		return -ENODEV;

	rc = qdio_shutdown(cdev, how);

	qdio_free(cdev);
	return rc;
}