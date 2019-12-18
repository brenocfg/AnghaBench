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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u16 ;
struct b43_phy {struct b43_phy_g* g; } ;
struct b43_wldev {int /*<<< orphan*/  wl; struct b43_phy phy; } ;
struct TYPE_5__ {int len; struct b43_rfatt* list; } ;
struct TYPE_4__ {int len; struct b43_bbatt* list; } ;
struct b43_txpower_lo_control {int power_vector; int* dc_lt; TYPE_2__ rfatt_list; TYPE_1__ bbatt_list; } ;
struct b43_rfatt {int dummy; } ;
struct b43_phy_g {struct b43_txpower_lo_control* lo_control; } ;
struct TYPE_6__ {scalar_t__ i; scalar_t__ q; } ;
struct b43_lo_calib {TYPE_3__ ctl; } ;
struct b43_bbatt {int dummy; } ;

/* Variables and functions */
 int B43_DC_LT_SIZE ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 struct b43_lo_calib* b43_calibrate_lo_setting (struct b43_wldev*,struct b43_bbatt const*,struct b43_rfatt const*) ; 
 int /*<<< orphan*/  b43_mac_enable (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_mac_suspend (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct b43_lo_calib*) ; 

void b43_gphy_dc_lt_init(struct b43_wldev *dev, bool update_all)
{
	struct b43_phy *phy = &dev->phy;
	struct b43_phy_g *gphy = phy->g;
	struct b43_txpower_lo_control *lo = gphy->lo_control;
	int i;
	int rf_offset, bb_offset;
	const struct b43_rfatt *rfatt;
	const struct b43_bbatt *bbatt;
	u64 power_vector;
	bool table_changed = false;

	BUILD_BUG_ON(B43_DC_LT_SIZE != 32);
	B43_WARN_ON(lo->rfatt_list.len * lo->bbatt_list.len > 64);

	power_vector = lo->power_vector;
	if (!update_all && !power_vector)
		return; /* Nothing to do. */

	/* Suspend the MAC now to avoid continuous suspend/enable
	 * cycles in the loop. */
	b43_mac_suspend(dev);

	for (i = 0; i < B43_DC_LT_SIZE * 2; i++) {
		struct b43_lo_calib *cal;
		int idx;
		u16 val;

		if (!update_all && !(power_vector & (((u64)1ULL) << i)))
			continue;
		/* Update the table entry for this power_vector bit.
		 * The table rows are RFatt entries and columns are BBatt. */
		bb_offset = i / lo->rfatt_list.len;
		rf_offset = i % lo->rfatt_list.len;
		bbatt = &(lo->bbatt_list.list[bb_offset]);
		rfatt = &(lo->rfatt_list.list[rf_offset]);

		cal = b43_calibrate_lo_setting(dev, bbatt, rfatt);
		if (!cal) {
			b43warn(dev->wl, "LO: Could not "
				"calibrate DC table entry\n");
			continue;
		}
		/*FIXME: Is Q really in the low nibble? */
		val = (u8)(cal->ctl.q);
		val |= ((u8)(cal->ctl.i)) << 4;
		kfree(cal);

		/* Get the index into the hardware DC LT. */
		idx = i / 2;
		/* Change the table in memory. */
		if (i % 2) {
			/* Change the high byte. */
			lo->dc_lt[idx] = (lo->dc_lt[idx] & 0x00FF)
					 | ((val & 0x00FF) << 8);
		} else {
			/* Change the low byte. */
			lo->dc_lt[idx] = (lo->dc_lt[idx] & 0xFF00)
					 | (val & 0x00FF);
		}
		table_changed = true;
	}
	if (table_changed) {
		/* The table changed in memory. Update the hardware table. */
		for (i = 0; i < B43_DC_LT_SIZE; i++)
			b43_phy_write(dev, 0x3A0 + i, lo->dc_lt[i]);
	}
	b43_mac_enable(dev);
}