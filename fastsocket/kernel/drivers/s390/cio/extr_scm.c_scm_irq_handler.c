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
struct scm_driver {int /*<<< orphan*/  (* handler ) (struct scm_device*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  driver; } ;
struct scm_device {TYPE_2__ dev; } ;
struct aob_rq_header {int /*<<< orphan*/  data; struct scm_device* scmdev; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct aob {TYPE_1__ request; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct scm_device*,int /*<<< orphan*/ ,int) ; 
 struct scm_driver* to_scm_drv (int /*<<< orphan*/ ) ; 

void scm_irq_handler(struct aob *aob, int error)
{
	struct aob_rq_header *aobrq = (void *) aob->request.data;
	struct scm_device *scmdev = aobrq->scmdev;
	struct scm_driver *scmdrv = to_scm_drv(scmdev->dev.driver);

	scmdrv->handler(scmdev, aobrq->data, error);
}