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
typedef  int /*<<< orphan*/  u8 ;
struct link_qual {int /*<<< orphan*/  vgc_level_reg; } ;
struct TYPE_6__ {scalar_t__ count; struct link_qual qual; } ;
struct rt2x00_dev {TYPE_2__* ops; TYPE_3__ link; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {TYPE_1__* lib; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* reset_tuner ) (struct rt2x00_dev*,struct link_qual*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  memset (struct link_qual*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00link_antenna_reset (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  stub1 (struct rt2x00_dev*,struct link_qual*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2x00link_reset_tuner(struct rt2x00_dev *rt2x00dev, bool antenna)
{
	struct link_qual *qual = &rt2x00dev->link.qual;
	u8 vgc_level = qual->vgc_level_reg;

	if (!test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		return;

	/*
	 * Reset link information.
	 * Both the currently active vgc level as well as
	 * the link tuner counter should be reset. Resetting
	 * the counter is important for devices where the
	 * device should only perform link tuning during the
	 * first minute after being enabled.
	 */
	rt2x00dev->link.count = 0;
	memset(qual, 0, sizeof(*qual));

	/*
	 * Restore the VGC level as stored in the registers,
	 * the driver can use this to determine if the register
	 * must be updated during reset or not.
	 */
	qual->vgc_level_reg = vgc_level;

	/*
	 * Reset the link tuner.
	 */
	rt2x00dev->ops->lib->reset_tuner(rt2x00dev, qual);

	if (antenna)
		rt2x00link_antenna_reset(rt2x00dev);
}