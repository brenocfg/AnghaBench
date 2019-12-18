#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ pvrf; } ;
struct TYPE_22__ {TYPE_6__ erw; } ;
struct TYPE_23__ {TYPE_7__ esw0; } ;
struct TYPE_16__ {int dstat; } ;
struct TYPE_15__ {TYPE_1__ cmd; } ;
struct irb {TYPE_8__ esw; TYPE_11__ scsw; } ;
struct ccw_device {TYPE_10__* private; } ;
struct TYPE_24__ {int doverify; scalar_t__ dosense; } ;
struct TYPE_17__ {int cons; } ;
struct TYPE_18__ {TYPE_2__ erw; } ;
struct TYPE_19__ {TYPE_3__ esw0; } ;
struct TYPE_20__ {TYPE_4__ esw; } ;
struct TYPE_14__ {TYPE_9__ flags; TYPE_5__ irb; } ;

/* Variables and functions */
 int DEV_STAT_CHN_END ; 
 int DEV_STAT_UNIT_CHECK ; 
 int SCSW_STCTL_STATUS_PEND ; 
 scalar_t__ ccw_device_accumulate_esw_valid (struct irb*) ; 
 int /*<<< orphan*/  ccw_device_msg_control_check (struct ccw_device*,struct irb*) ; 
 int /*<<< orphan*/  ccw_device_path_notoper (struct ccw_device*) ; 
 scalar_t__ scsw_is_valid_pno (TYPE_11__*) ; 
 scalar_t__ scsw_pno (TYPE_11__*) ; 
 int scsw_stctl (TYPE_11__*) ; 

void
ccw_device_accumulate_basic_sense(struct ccw_device *cdev, struct irb *irb)
{
	/*
	 * Check if the status pending bit is set in stctl.
	 * If not, the remaining bit have no meaning and we must ignore them.
	 * The esw is not meaningful as well...
	 */
	if (!(scsw_stctl(&irb->scsw) & SCSW_STCTL_STATUS_PEND))
		return;

	/* Check for channel checks and interface control checks. */
	ccw_device_msg_control_check(cdev, irb);

	/* Check for path not operational. */
	if (scsw_is_valid_pno(&irb->scsw) && scsw_pno(&irb->scsw))
		ccw_device_path_notoper(cdev);

	if (!(irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) &&
	    (irb->scsw.cmd.dstat & DEV_STAT_CHN_END)) {
		cdev->private->irb.esw.esw0.erw.cons = 1;
		cdev->private->flags.dosense = 0;
	}
	/* Check if path verification is required. */
	if (ccw_device_accumulate_esw_valid(irb) &&
	    irb->esw.esw0.erw.pvrf)
		cdev->private->flags.doverify = 1;
}