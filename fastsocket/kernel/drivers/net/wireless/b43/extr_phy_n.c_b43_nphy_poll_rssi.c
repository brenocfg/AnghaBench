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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int rev; } ;
struct b43_wldev {TYPE_1__ phy; } ;
typedef  int s8 ;
typedef  int s32 ;
typedef  enum n_rssi_type { ____Placeholder_n_rssi_type } n_rssi_type ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_AFECTL_C1 ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_C2 ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_OVER ; 
 int /*<<< orphan*/  B43_NPHY_AFECTL_OVER1 ; 
 int /*<<< orphan*/  B43_NPHY_GPIO_HIOUT ; 
 int /*<<< orphan*/  B43_NPHY_GPIO_LOOUT ; 
 int /*<<< orphan*/  B43_NPHY_GPIO_SEL ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_CMD ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_LUT_TRSW_UP1 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_LUT_TRSW_UP2 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_OVER ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_RSSIO1 ; 
 int /*<<< orphan*/  B43_NPHY_RFCTL_RSSIO2 ; 
 int /*<<< orphan*/  B43_NPHY_RSSI1 ; 
 int /*<<< orphan*/  B43_NPHY_RSSI2 ; 
 int /*<<< orphan*/  B43_NPHY_TXF_40CO_B1S0 ; 
 int /*<<< orphan*/  B43_NPHY_TXF_40CO_B32S1 ; 
 int /*<<< orphan*/  b43_nphy_rssi_select (struct b43_wldev*,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int b43_nphy_poll_rssi(struct b43_wldev *dev, enum n_rssi_type rssi_type,
			      s32 *buf, u8 nsamp)
{
	int i;
	int out;
	u16 save_regs_phy[9];
	u16 s[2];

	if (dev->phy.rev >= 3) {
		save_regs_phy[0] = b43_phy_read(dev, B43_NPHY_AFECTL_C1);
		save_regs_phy[1] = b43_phy_read(dev, B43_NPHY_AFECTL_C2);
		save_regs_phy[2] = b43_phy_read(dev,
						B43_NPHY_RFCTL_LUT_TRSW_UP1);
		save_regs_phy[3] = b43_phy_read(dev,
						B43_NPHY_RFCTL_LUT_TRSW_UP2);
		save_regs_phy[4] = b43_phy_read(dev, B43_NPHY_AFECTL_OVER1);
		save_regs_phy[5] = b43_phy_read(dev, B43_NPHY_AFECTL_OVER);
		save_regs_phy[6] = b43_phy_read(dev, B43_NPHY_TXF_40CO_B1S0);
		save_regs_phy[7] = b43_phy_read(dev, B43_NPHY_TXF_40CO_B32S1);
		save_regs_phy[8] = 0;
	} else {
		save_regs_phy[0] = b43_phy_read(dev, B43_NPHY_AFECTL_C1);
		save_regs_phy[1] = b43_phy_read(dev, B43_NPHY_AFECTL_C2);
		save_regs_phy[2] = b43_phy_read(dev, B43_NPHY_AFECTL_OVER);
		save_regs_phy[3] = b43_phy_read(dev, B43_NPHY_RFCTL_CMD);
		save_regs_phy[4] = b43_phy_read(dev, B43_NPHY_RFCTL_OVER);
		save_regs_phy[5] = b43_phy_read(dev, B43_NPHY_RFCTL_RSSIO1);
		save_regs_phy[6] = b43_phy_read(dev, B43_NPHY_RFCTL_RSSIO2);
		save_regs_phy[7] = 0;
		save_regs_phy[8] = 0;
	}

	b43_nphy_rssi_select(dev, 5, rssi_type);

	if (dev->phy.rev < 2) {
		save_regs_phy[8] = b43_phy_read(dev, B43_NPHY_GPIO_SEL);
		b43_phy_write(dev, B43_NPHY_GPIO_SEL, 5);
	}

	for (i = 0; i < 4; i++)
		buf[i] = 0;

	for (i = 0; i < nsamp; i++) {
		if (dev->phy.rev < 2) {
			s[0] = b43_phy_read(dev, B43_NPHY_GPIO_LOOUT);
			s[1] = b43_phy_read(dev, B43_NPHY_GPIO_HIOUT);
		} else {
			s[0] = b43_phy_read(dev, B43_NPHY_RSSI1);
			s[1] = b43_phy_read(dev, B43_NPHY_RSSI2);
		}

		buf[0] += ((s8)((s[0] & 0x3F) << 2)) >> 2;
		buf[1] += ((s8)(((s[0] >> 8) & 0x3F) << 2)) >> 2;
		buf[2] += ((s8)((s[1] & 0x3F) << 2)) >> 2;
		buf[3] += ((s8)(((s[1] >> 8) & 0x3F) << 2)) >> 2;
	}
	out = (buf[0] & 0xFF) << 24 | (buf[1] & 0xFF) << 16 |
		(buf[2] & 0xFF) << 8 | (buf[3] & 0xFF);

	if (dev->phy.rev < 2)
		b43_phy_write(dev, B43_NPHY_GPIO_SEL, save_regs_phy[8]);

	if (dev->phy.rev >= 3) {
		b43_phy_write(dev, B43_NPHY_AFECTL_C1, save_regs_phy[0]);
		b43_phy_write(dev, B43_NPHY_AFECTL_C2, save_regs_phy[1]);
		b43_phy_write(dev, B43_NPHY_RFCTL_LUT_TRSW_UP1,
				save_regs_phy[2]);
		b43_phy_write(dev, B43_NPHY_RFCTL_LUT_TRSW_UP2,
				save_regs_phy[3]);
		b43_phy_write(dev, B43_NPHY_AFECTL_OVER1, save_regs_phy[4]);
		b43_phy_write(dev, B43_NPHY_AFECTL_OVER, save_regs_phy[5]);
		b43_phy_write(dev, B43_NPHY_TXF_40CO_B1S0, save_regs_phy[6]);
		b43_phy_write(dev, B43_NPHY_TXF_40CO_B32S1, save_regs_phy[7]);
	} else {
		b43_phy_write(dev, B43_NPHY_AFECTL_C1, save_regs_phy[0]);
		b43_phy_write(dev, B43_NPHY_AFECTL_C2, save_regs_phy[1]);
		b43_phy_write(dev, B43_NPHY_AFECTL_OVER, save_regs_phy[2]);
		b43_phy_write(dev, B43_NPHY_RFCTL_CMD, save_regs_phy[3]);
		b43_phy_write(dev, B43_NPHY_RFCTL_OVER, save_regs_phy[4]);
		b43_phy_write(dev, B43_NPHY_RFCTL_RSSIO1, save_regs_phy[5]);
		b43_phy_write(dev, B43_NPHY_RFCTL_RSSIO2, save_regs_phy[6]);
	}

	return out;
}