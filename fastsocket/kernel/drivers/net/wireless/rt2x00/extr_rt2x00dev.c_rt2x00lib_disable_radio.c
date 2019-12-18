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
struct rt2x00_dev {TYPE_1__* ops; int /*<<< orphan*/  cap_flags; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_device_state ) (struct rt2x00_dev*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {TYPE_2__* lib; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPABILITY_VCO_RECALIBRATION ; 
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  STATE_RADIO_IRQ_OFF ; 
 int /*<<< orphan*/  STATE_RADIO_OFF ; 
 int /*<<< orphan*/  rt2x00led_led_activity (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2x00leds_led_radio (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2x00link_stop_agc (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00link_stop_tuner (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00link_stop_vcocal (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00link_stop_watchdog (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00queue_flush_queues (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2x00queue_stop_queues (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  stub1 (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2x00lib_disable_radio(struct rt2x00_dev *rt2x00dev)
{
	if (!test_and_clear_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		return;

	/*
	 * Stop watchdog monitoring.
	 */
	rt2x00link_stop_watchdog(rt2x00dev);

	/*
	 * Stop all queues
	 */
	rt2x00link_stop_agc(rt2x00dev);
	if (test_bit(CAPABILITY_VCO_RECALIBRATION, &rt2x00dev->cap_flags))
		rt2x00link_stop_vcocal(rt2x00dev);
	rt2x00link_stop_tuner(rt2x00dev);
	rt2x00queue_stop_queues(rt2x00dev);
	rt2x00queue_flush_queues(rt2x00dev, true);

	/*
	 * Disable radio.
	 */
	rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_RADIO_OFF);
	rt2x00dev->ops->lib->set_device_state(rt2x00dev, STATE_RADIO_IRQ_OFF);
	rt2x00led_led_activity(rt2x00dev, false);
	rt2x00leds_led_radio(rt2x00dev, false);
}