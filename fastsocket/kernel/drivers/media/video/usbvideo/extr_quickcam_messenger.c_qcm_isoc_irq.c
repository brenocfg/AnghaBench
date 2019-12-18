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
struct TYPE_2__ {int urb_length; int data_count; int /*<<< orphan*/  urb_count; } ;
struct uvd {int /*<<< orphan*/  dp; TYPE_1__ stats; int /*<<< orphan*/  streaming; } ;
struct urb {int /*<<< orphan*/  actual_length; struct uvd* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAMERA_IS_OPERATIONAL (struct uvd*) ; 
 int /*<<< orphan*/  RingQueue_WakeUpInterruptible (int /*<<< orphan*/ *) ; 
 int qcm_compress_iso (struct uvd*,struct urb*) ; 
 int /*<<< orphan*/  resubmit_urb (struct uvd*,struct urb*) ; 

__attribute__((used)) static void qcm_isoc_irq(struct urb *urb)
{
	int len;
	struct uvd *uvd = urb->context;

	if (!CAMERA_IS_OPERATIONAL(uvd))
		return;

	if (!uvd->streaming)
		return;

	uvd->stats.urb_count++;

	if (!urb->actual_length) {
		resubmit_urb(uvd, urb);
		return;
	}

	len = qcm_compress_iso(uvd, urb);
	resubmit_urb(uvd, urb);
	uvd->stats.urb_length = len;
	uvd->stats.data_count += len;
	if (len)
		RingQueue_WakeUpInterruptible(&uvd->dp);
}