#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u16 ;
struct b43_phy {struct b43_phy_g* g; } ;
struct b43_wldev {struct b43_phy phy; } ;
struct b43_phy_g {int /*<<< orphan*/  trsw_rx_gain; int /*<<< orphan*/  pga_gain; int /*<<< orphan*/  lna_gain; } ;
struct b43_loctl {scalar_t__ i; scalar_t__ q; } ;
struct b43_lo_g_statemachine {int nr_measured; int state_val_multiplier; int lowest_feedth; int current_state; struct b43_loctl min_loctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_lo_write (struct b43_wldev*,struct b43_loctl*) ; 
 scalar_t__ has_loopback_gain (struct b43_phy*) ; 
 int lo_measure_feedthrough (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lo_measure_gain_values (struct b43_wldev*,int,scalar_t__) ; 
 int lo_probe_possible_loctls (struct b43_wldev*,struct b43_loctl*,struct b43_lo_g_statemachine*) ; 
 int /*<<< orphan*/  memcpy (struct b43_loctl*,struct b43_loctl*,int) ; 

__attribute__((used)) static void lo_probe_loctls_statemachine(struct b43_wldev *dev,
					 struct b43_loctl *loctl,
					 int *max_rx_gain)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	struct b43_lo_g_statemachine d;
	u16 feedth;
	int found_lower;
	struct b43_loctl probe_loctl;
	int max_repeat = 1, repeat_cnt = 0;

	d.nr_measured = 0;
	d.state_val_multiplier = 1;
	if (has_loopback_gain(phy))
		d.state_val_multiplier = 3;

	memcpy(&d.min_loctl, loctl, sizeof(struct b43_loctl));
	if (has_loopback_gain(phy))
		max_repeat = 4;
	do {
		b43_lo_write(dev, &d.min_loctl);
		feedth = lo_measure_feedthrough(dev, gphy->lna_gain,
						gphy->pga_gain,
						gphy->trsw_rx_gain);
		if (feedth < 0x258) {
			if (feedth >= 0x12C)
				*max_rx_gain += 6;
			else
				*max_rx_gain += 3;
			feedth = lo_measure_feedthrough(dev, gphy->lna_gain,
							gphy->pga_gain,
							gphy->trsw_rx_gain);
		}
		d.lowest_feedth = feedth;

		d.current_state = 0;
		do {
			B43_WARN_ON(!
				    (d.current_state >= 0
				     && d.current_state <= 8));
			memcpy(&probe_loctl, &d.min_loctl,
			       sizeof(struct b43_loctl));
			found_lower =
			    lo_probe_possible_loctls(dev, &probe_loctl, &d);
			if (!found_lower)
				break;
			if ((probe_loctl.i == d.min_loctl.i) &&
			    (probe_loctl.q == d.min_loctl.q))
				break;
			memcpy(&d.min_loctl, &probe_loctl,
			       sizeof(struct b43_loctl));
			d.nr_measured++;
		} while (d.nr_measured < 24);
		memcpy(loctl, &d.min_loctl, sizeof(struct b43_loctl));

		if (has_loopback_gain(phy)) {
			if (d.lowest_feedth > 0x1194)
				*max_rx_gain -= 6;
			else if (d.lowest_feedth < 0x5DC)
				*max_rx_gain += 3;
			if (repeat_cnt == 0) {
				if (d.lowest_feedth <= 0x5DC) {
					d.state_val_multiplier = 1;
					repeat_cnt++;
				} else
					d.state_val_multiplier = 2;
			} else if (repeat_cnt == 2)
				d.state_val_multiplier = 1;
		}
		lo_measure_gain_values(dev, *max_rx_gain,
				       has_loopback_gain(phy));
	} while (++repeat_cnt < max_repeat);
}