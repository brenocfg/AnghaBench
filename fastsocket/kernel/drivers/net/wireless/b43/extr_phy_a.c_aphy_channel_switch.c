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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int,int,int) ; 
 int b43_radio_read16 (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_radio_set_tx_iq (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_radio_write16 (struct b43_wldev*,int,int) ; 
 int /*<<< orphan*/  b43_write16 (struct b43_wldev*,int,int) ; 
 int channel2freq_a (unsigned int) ; 
 int freq_r3A_value (int) ; 

__attribute__((used)) static void aphy_channel_switch(struct b43_wldev *dev, unsigned int channel)
{
	u16 freq, r8, tmp;

	freq = channel2freq_a(channel);

	r8 = b43_radio_read16(dev, 0x0008);
	b43_write16(dev, 0x03F0, freq);
	b43_radio_write16(dev, 0x0008, r8);

	//TODO: write max channel TX power? to Radio 0x2D
	tmp = b43_radio_read16(dev, 0x002E);
	tmp &= 0x0080;
	//TODO: OR tmp with the Power out estimation for this channel?
	b43_radio_write16(dev, 0x002E, tmp);

	if (freq >= 4920 && freq <= 5500) {
		/*
		 * r8 = (((freq * 15 * 0xE1FC780F) >> 32) / 29) & 0x0F;
		 *    = (freq * 0.025862069
		 */
		r8 = 3 * freq / 116;	/* is equal to r8 = freq * 0.025862 */
	}
	b43_radio_write16(dev, 0x0007, (r8 << 4) | r8);
	b43_radio_write16(dev, 0x0020, (r8 << 4) | r8);
	b43_radio_write16(dev, 0x0021, (r8 << 4) | r8);
	b43_radio_maskset(dev, 0x0022, 0x000F, (r8 << 4));
	b43_radio_write16(dev, 0x002A, (r8 << 4));
	b43_radio_write16(dev, 0x002B, (r8 << 4));
	b43_radio_maskset(dev, 0x0008, 0x00F0, (r8 << 4));
	b43_radio_maskset(dev, 0x0029, 0xFF0F, 0x00B0);
	b43_radio_write16(dev, 0x0035, 0x00AA);
	b43_radio_write16(dev, 0x0036, 0x0085);
	b43_radio_maskset(dev, 0x003A, 0xFF20, freq_r3A_value(freq));
	b43_radio_mask(dev, 0x003D, 0x00FF);
	b43_radio_maskset(dev, 0x0081, 0xFF7F, 0x0080);
	b43_radio_mask(dev, 0x0035, 0xFFEF);
	b43_radio_maskset(dev, 0x0035, 0xFFEF, 0x0010);
	b43_radio_set_tx_iq(dev);
	//TODO: TSSI2dbm workaround
//FIXME	b43_phy_xmitpower(dev);
}