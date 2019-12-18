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
typedef  int const u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int,int) ; 
 int b43_radio_read16 (struct b43_wldev*,int) ; 

__attribute__((used)) static void b43_radio_set_tx_iq(struct b43_wldev *dev)
{
	static const u8 data_high[5] = { 0x00, 0x40, 0x80, 0x90, 0xD0 };
	static const u8 data_low[5] = { 0x00, 0x01, 0x05, 0x06, 0x0A };
	u16 tmp = b43_radio_read16(dev, 0x001E);
	int i, j;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (tmp == (data_high[i] << 4 | data_low[j])) {
				b43_phy_write(dev, 0x0069,
					      (i - j) << 8 | 0x00C0);
				return;
			}
		}
	}
}