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
struct antenna_setup {scalar_t__ rx; scalar_t__ tx; } ;
struct link_ant {int flags; struct antenna_setup active; } ;
struct TYPE_4__ {struct link_ant ant; } ;
struct rt2x00_dev {int /*<<< orphan*/  rx; int /*<<< orphan*/  flags; TYPE_3__* ops; TYPE_1__ link; struct antenna_setup default_ant; } ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_6__ {TYPE_2__* lib; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* config_ant ) (struct rt2x00_dev*,struct antenna_setup*) ;} ;

/* Variables and functions */
 void* ANTENNA_B ; 
 int ANTENNA_RX_DIVERSITY ; 
 scalar_t__ ANTENNA_SW_DIVERSITY ; 
 int ANTENNA_TX_DIVERSITY ; 
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  memcpy (struct antenna_setup*,struct antenna_setup*,int) ; 
 int /*<<< orphan*/  rt2x00link_reset_tuner (struct rt2x00_dev*,int) ; 
 int /*<<< orphan*/  rt2x00queue_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00queue_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rt2x00_dev*,struct antenna_setup*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2x00lib_config_antenna(struct rt2x00_dev *rt2x00dev,
			      struct antenna_setup config)
{
	struct link_ant *ant = &rt2x00dev->link.ant;
	struct antenna_setup *def = &rt2x00dev->default_ant;
	struct antenna_setup *active = &rt2x00dev->link.ant.active;

	/*
	 * When the caller tries to send the SW diversity,
	 * we must update the ANTENNA_RX_DIVERSITY flag to
	 * enable the antenna diversity in the link tuner.
	 *
	 * Secondly, we must guarentee we never send the
	 * software antenna diversity command to the driver.
	 */
	if (!(ant->flags & ANTENNA_RX_DIVERSITY)) {
		if (config.rx == ANTENNA_SW_DIVERSITY) {
			ant->flags |= ANTENNA_RX_DIVERSITY;

			if (def->rx == ANTENNA_SW_DIVERSITY)
				config.rx = ANTENNA_B;
			else
				config.rx = def->rx;
		}
	} else if (config.rx == ANTENNA_SW_DIVERSITY)
		config.rx = active->rx;

	if (!(ant->flags & ANTENNA_TX_DIVERSITY)) {
		if (config.tx == ANTENNA_SW_DIVERSITY) {
			ant->flags |= ANTENNA_TX_DIVERSITY;

			if (def->tx == ANTENNA_SW_DIVERSITY)
				config.tx = ANTENNA_B;
			else
				config.tx = def->tx;
		}
	} else if (config.tx == ANTENNA_SW_DIVERSITY)
		config.tx = active->tx;

	/*
	 * Antenna setup changes require the RX to be disabled,
	 * else the changes will be ignored by the device.
	 */
	if (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt2x00queue_stop_queue(rt2x00dev->rx);

	/*
	 * Write new antenna setup to device and reset the link tuner.
	 * The latter is required since we need to recalibrate the
	 * noise-sensitivity ratio for the new setup.
	 */
	rt2x00dev->ops->lib->config_ant(rt2x00dev, &config);

	rt2x00link_reset_tuner(rt2x00dev, true);

	memcpy(active, &config, sizeof(config));

	if (test_bit(DEVICE_STATE_ENABLED_RADIO, &rt2x00dev->flags))
		rt2x00queue_start_queue(rt2x00dev->rx);
}