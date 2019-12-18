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
typedef  int u8 ;
struct b43legacy_wldev {int dummy; } ;
struct b43legacy_txstatus {int frame_count; int rts_count; int supp_reason; int pm_indicated; int intermediate; int for_ampdu; int acked; int /*<<< orphan*/  phy_stat; void* seq; void* cookie; } ;
struct b43legacy_hwtxstatus {int count; int flags; int /*<<< orphan*/  phy_stat; int /*<<< orphan*/  seq; int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43legacy_handle_txstatus (struct b43legacy_wldev*,struct b43legacy_txstatus*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 

void b43legacy_handle_hwtxstatus(struct b43legacy_wldev *dev,
				 const struct b43legacy_hwtxstatus *hw)
{
	struct b43legacy_txstatus status;
	u8 tmp;

	status.cookie = le16_to_cpu(hw->cookie);
	status.seq = le16_to_cpu(hw->seq);
	status.phy_stat = hw->phy_stat;
	tmp = hw->count;
	status.frame_count = (tmp >> 4);
	status.rts_count = (tmp & 0x0F);
	tmp = hw->flags << 1;
	status.supp_reason = ((tmp & 0x1C) >> 2);
	status.pm_indicated = !!(tmp & 0x80);
	status.intermediate = !!(tmp & 0x40);
	status.for_ampdu = !!(tmp & 0x20);
	status.acked = !!(tmp & 0x02);

	b43legacy_handle_txstatus(dev, &status);
}