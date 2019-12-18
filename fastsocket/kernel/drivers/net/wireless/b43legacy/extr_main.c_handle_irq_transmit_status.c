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
typedef  int u32 ;
typedef  int u16 ;
struct b43legacy_wldev {int dummy; } ;
struct b43legacy_txstatus {int cookie; int seq; int phy_stat; int frame_count; int rts_count; int supp_reason; int pm_indicated; int intermediate; int for_ampdu; int acked; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_MMIO_XMITSTAT_0 ; 
 int /*<<< orphan*/  B43legacy_MMIO_XMITSTAT_1 ; 
 int /*<<< orphan*/  b43legacy_handle_txstatus (struct b43legacy_wldev*,struct b43legacy_txstatus*) ; 
 int b43legacy_read32 (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_irq_transmit_status(struct b43legacy_wldev *dev)
{
	u32 v0;
	u32 v1;
	u16 tmp;
	struct b43legacy_txstatus stat;

	while (1) {
		v0 = b43legacy_read32(dev, B43legacy_MMIO_XMITSTAT_0);
		if (!(v0 & 0x00000001))
			break;
		v1 = b43legacy_read32(dev, B43legacy_MMIO_XMITSTAT_1);

		stat.cookie = (v0 >> 16);
		stat.seq = (v1 & 0x0000FFFF);
		stat.phy_stat = ((v1 & 0x00FF0000) >> 16);
		tmp = (v0 & 0x0000FFFF);
		stat.frame_count = ((tmp & 0xF000) >> 12);
		stat.rts_count = ((tmp & 0x0F00) >> 8);
		stat.supp_reason = ((tmp & 0x001C) >> 2);
		stat.pm_indicated = !!(tmp & 0x0080);
		stat.intermediate = !!(tmp & 0x0040);
		stat.for_ampdu = !!(tmp & 0x0020);
		stat.acked = !!(tmp & 0x0002);

		b43legacy_handle_txstatus(dev, &stat);
	}
}