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
struct TYPE_4__ {int rx; } ;
struct link_ant {int flags; TYPE_2__ active; } ;
struct TYPE_3__ {struct link_ant ant; } ;
struct rt2x00_dev {TYPE_1__ link; } ;
struct antenna_setup {int rx; int tx; } ;
typedef  int /*<<< orphan*/  new_ant ;

/* Variables and functions */
 int ANTENNA_A ; 
 int ANTENNA_B ; 
 int ANTENNA_MODE_SAMPLE ; 
 int ANTENNA_RX_DIVERSITY ; 
 int ANTENNA_TX_DIVERSITY ; 
 int /*<<< orphan*/  memcpy (struct antenna_setup*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  rt2x00lib_config_antenna (struct rt2x00_dev*,struct antenna_setup) ; 
 int rt2x00link_antenna_get_link_rssi (struct rt2x00_dev*) ; 
 int rt2x00link_antenna_get_rssi_history (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00link_antenna_update_rssi_history (struct rt2x00_dev*,int) ; 

__attribute__((used)) static void rt2x00lib_antenna_diversity_sample(struct rt2x00_dev *rt2x00dev)
{
	struct link_ant *ant = &rt2x00dev->link.ant;
	struct antenna_setup new_ant;
	int other_antenna;

	int sample_current = rt2x00link_antenna_get_link_rssi(rt2x00dev);
	int sample_other = rt2x00link_antenna_get_rssi_history(rt2x00dev);

	memcpy(&new_ant, &ant->active, sizeof(new_ant));

	/*
	 * We are done sampling. Now we should evaluate the results.
	 */
	ant->flags &= ~ANTENNA_MODE_SAMPLE;

	/*
	 * During the last period we have sampled the RSSI
	 * from both antennas. It now is time to determine
	 * which antenna demonstrated the best performance.
	 * When we are already on the antenna with the best
	 * performance, just create a good starting point
	 * for the history and we are done.
	 */
	if (sample_current >= sample_other) {
		rt2x00link_antenna_update_rssi_history(rt2x00dev,
			sample_current);
		return;
	}

	other_antenna = (ant->active.rx == ANTENNA_A) ? ANTENNA_B : ANTENNA_A;

	if (ant->flags & ANTENNA_RX_DIVERSITY)
		new_ant.rx = other_antenna;

	if (ant->flags & ANTENNA_TX_DIVERSITY)
		new_ant.tx = other_antenna;

	rt2x00lib_config_antenna(rt2x00dev, new_ant);
}