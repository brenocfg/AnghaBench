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
struct rt2x00_dev {int /*<<< orphan*/  cap_flags; int /*<<< orphan*/  flags; TYPE_2__* ops; } ;
struct TYPE_4__ {TYPE_1__* lib; } ;
struct TYPE_3__ {int (* set_device_state ) (struct rt2x00_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAPABILITY_VCO_RECALIBRATION ; 
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  STATE_RADIO_IRQ_ON ; 
 int /*<<< orphan*/  STATE_RADIO_ON ; 
 int /*<<< orphan*/  rt2x00led_led_activity (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2x00leds_led_radio (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2x00link_start_agc (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00link_start_tuner (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00link_start_vcocal (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00link_start_watchdog (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00queue_init_queues (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00queue_start_queues (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int stub2 (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rt2x00lib_enable_radio(struct rt2x00_dev *rt2x00dev)
{
	int status;

	/*
	 * Don't enable the radio twice.
	 * And check if the hardware button has been disabled.
	 */
	if (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		return 0;

	/*
	 * Initialize all data queues.
	 */
	rt2x00queue_init_queues(rt2x00dev);

	/*
	 * Enable radio.
	 */
	status =
	    rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_RADIO_ON);
	if (status)
		return status;

	rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_RADIO_IRQ_ON);

	rt2x00leds_led_radio(rt2x00dev, true);
	rt2x00led_led_activity(rt2x00dev, true);

	set_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags);

	/*
	 * Enable queues.
	 */
	rt2x00queue_start_queues(rt2x00dev);
	rt2x00link_start_tuner(rt2x00dev);
	rt2x00link_start_agc(rt2x00dev);
	if (test_bit(CAPABILITY_VCO_RECALIBRATION, &rt2x00dev->cap_flags))
		rt2x00link_start_vcocal(rt2x00dev);

	/*
	 * Start watchdog monitoring.
	 */
	rt2x00link_start_watchdog(rt2x00dev);

	return 0;
}