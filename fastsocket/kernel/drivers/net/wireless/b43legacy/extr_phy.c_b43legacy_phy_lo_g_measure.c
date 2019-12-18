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
typedef  int u16 ;
struct b43legacy_phy {int channel; int txctl2; struct b43legacy_lopair* _lo_pairs; scalar_t__ gmode; } ;
struct b43legacy_wldev {int /*<<< orphan*/  wl; struct b43legacy_phy phy; } ;
struct b43legacy_lopair {int low; int high; int /*<<< orphan*/  used; } ;
typedef  int /*<<< orphan*/  control ;

/* Variables and functions */
 int B43legacy_LO_COUNT ; 
 int B43legacy_MMIO_CHANNEL_EXT ; 
 int B43legacy_PHY_G_CRS ; 
 scalar_t__ B43legacy_STAT_STARTED ; 
 int /*<<< orphan*/  b43legacy_dummy_transmission (struct b43legacy_wldev*) ; 
 struct b43legacy_lopair* b43legacy_get_lopair (struct b43legacy_phy*,int,int) ; 
 int /*<<< orphan*/  b43legacy_phy_lo_adjust (struct b43legacy_wldev*,int const) ; 
 int /*<<< orphan*/  b43legacy_phy_lo_g_measure_txctl2 (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_phy_lo_g_state (struct b43legacy_wldev*,struct b43legacy_lopair*,struct b43legacy_lopair*,int) ; 
 int b43legacy_phy_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_set_baseband_attenuation (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_write (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_radio_read16 (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_radio_selectchannel (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacy_radio_write16 (struct b43legacy_wldev*,int,int) ; 
 int b43legacy_read16 (struct b43legacy_wldev*,int) ; 
 scalar_t__ b43legacy_status (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_voluntary_preempt () ; 
 int /*<<< orphan*/  b43legacy_write16 (struct b43legacy_wldev*,int,int) ; 
 int /*<<< orphan*/  b43legacywarn (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  memcpy (struct b43legacy_lopair*,struct b43legacy_lopair*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void b43legacy_phy_lo_g_measure(struct b43legacy_wldev *dev)
{
	static const u8 pairorder[10] = { 3, 1, 5, 7, 9, 2, 0, 4, 6, 8 };
	const int is_initializing = (b43legacy_status(dev)
				     < B43legacy_STAT_STARTED);
	struct b43legacy_phy *phy = &dev->phy;
	u16 h;
	u16 i;
	u16 oldi = 0;
	u16 j;
	struct b43legacy_lopair control;
	struct b43legacy_lopair *tmp_control;
	u16 tmp;
	u16 regstack[16] = { 0 };
	u8 oldchannel;

	/* XXX: What are these? */
	u8 r27 = 0;
	u16 r31;

	oldchannel = phy->channel;
	/* Setup */
	if (phy->gmode) {
		regstack[0] = b43legacy_phy_read(dev, B43legacy_PHY_G_CRS);
		regstack[1] = b43legacy_phy_read(dev, 0x0802);
		b43legacy_phy_write(dev, B43legacy_PHY_G_CRS, regstack[0]
				    & 0x7FFF);
		b43legacy_phy_write(dev, 0x0802, regstack[1] & 0xFFFC);
	}
	regstack[3] = b43legacy_read16(dev, 0x03E2);
	b43legacy_write16(dev, 0x03E2, regstack[3] | 0x8000);
	regstack[4] = b43legacy_read16(dev, B43legacy_MMIO_CHANNEL_EXT);
	regstack[5] = b43legacy_phy_read(dev, 0x15);
	regstack[6] = b43legacy_phy_read(dev, 0x2A);
	regstack[7] = b43legacy_phy_read(dev, 0x35);
	regstack[8] = b43legacy_phy_read(dev, 0x60);
	regstack[9] = b43legacy_radio_read16(dev, 0x43);
	regstack[10] = b43legacy_radio_read16(dev, 0x7A);
	regstack[11] = b43legacy_radio_read16(dev, 0x52);
	if (phy->gmode) {
		regstack[12] = b43legacy_phy_read(dev, 0x0811);
		regstack[13] = b43legacy_phy_read(dev, 0x0812);
		regstack[14] = b43legacy_phy_read(dev, 0x0814);
		regstack[15] = b43legacy_phy_read(dev, 0x0815);
	}
	b43legacy_radio_selectchannel(dev, 6, 0);
	if (phy->gmode) {
		b43legacy_phy_write(dev, B43legacy_PHY_G_CRS, regstack[0]
				    & 0x7FFF);
		b43legacy_phy_write(dev, 0x0802, regstack[1] & 0xFFFC);
		b43legacy_dummy_transmission(dev);
	}
	b43legacy_radio_write16(dev, 0x0043, 0x0006);

	b43legacy_phy_set_baseband_attenuation(dev, 2);

	b43legacy_write16(dev, B43legacy_MMIO_CHANNEL_EXT, 0x0000);
	b43legacy_phy_write(dev, 0x002E, 0x007F);
	b43legacy_phy_write(dev, 0x080F, 0x0078);
	b43legacy_phy_write(dev, 0x0035, regstack[7] & ~(1 << 7));
	b43legacy_radio_write16(dev, 0x007A, regstack[10] & 0xFFF0);
	b43legacy_phy_write(dev, 0x002B, 0x0203);
	b43legacy_phy_write(dev, 0x002A, 0x08A3);
	if (phy->gmode) {
		b43legacy_phy_write(dev, 0x0814, regstack[14] | 0x0003);
		b43legacy_phy_write(dev, 0x0815, regstack[15] & 0xFFFC);
		b43legacy_phy_write(dev, 0x0811, 0x01B3);
		b43legacy_phy_write(dev, 0x0812, 0x00B2);
	}
	if (is_initializing)
		b43legacy_phy_lo_g_measure_txctl2(dev);
	b43legacy_phy_write(dev, 0x080F, 0x8078);

	/* Measure */
	control.low = 0;
	control.high = 0;
	for (h = 0; h < 10; h++) {
		/* Loop over each possible RadioAttenuation (0-9) */
		i = pairorder[h];
		if (is_initializing) {
			if (i == 3) {
				control.low = 0;
				control.high = 0;
			} else if (((i % 2 == 1) && (oldi % 2 == 1)) ||
				  ((i % 2 == 0) && (oldi % 2 == 0))) {
				tmp_control = b43legacy_get_lopair(phy, oldi,
								   0);
				memcpy(&control, tmp_control, sizeof(control));
			} else {
				tmp_control = b43legacy_get_lopair(phy, 3, 0);
				memcpy(&control, tmp_control, sizeof(control));
			}
		}
		/* Loop over each possible BasebandAttenuation/2 */
		for (j = 0; j < 4; j++) {
			if (is_initializing) {
				tmp = i * 2 + j;
				r27 = 0;
				r31 = 0;
				if (tmp > 14) {
					r31 = 1;
					if (tmp > 17)
						r27 = 1;
					if (tmp > 19)
						r27 = 2;
				}
			} else {
				tmp_control = b43legacy_get_lopair(phy, i,
								   j * 2);
				if (!tmp_control->used)
					continue;
				memcpy(&control, tmp_control, sizeof(control));
				r27 = 3;
				r31 = 0;
			}
			b43legacy_radio_write16(dev, 0x43, i);
			b43legacy_radio_write16(dev, 0x52, phy->txctl2);
			udelay(10);
			b43legacy_voluntary_preempt();

			b43legacy_phy_set_baseband_attenuation(dev, j * 2);

			tmp = (regstack[10] & 0xFFF0);
			if (r31)
				tmp |= 0x0008;
			b43legacy_radio_write16(dev, 0x007A, tmp);

			tmp_control = b43legacy_get_lopair(phy, i, j * 2);
			b43legacy_phy_lo_g_state(dev, &control, tmp_control,
						 r27);
		}
		oldi = i;
	}
	/* Loop over each possible RadioAttenuation (10-13) */
	for (i = 10; i < 14; i++) {
		/* Loop over each possible BasebandAttenuation/2 */
		for (j = 0; j < 4; j++) {
			if (is_initializing) {
				tmp_control = b43legacy_get_lopair(phy, i - 9,
								 j * 2);
				memcpy(&control, tmp_control, sizeof(control));
				/* FIXME: The next line is wrong, as the
				 * following if statement can never trigger. */
				tmp = (i - 9) * 2 + j - 5;
				r27 = 0;
				r31 = 0;
				if (tmp > 14) {
					r31 = 1;
					if (tmp > 17)
						r27 = 1;
					if (tmp > 19)
						r27 = 2;
				}
			} else {
				tmp_control = b43legacy_get_lopair(phy, i - 9,
								   j * 2);
				if (!tmp_control->used)
					continue;
				memcpy(&control, tmp_control, sizeof(control));
				r27 = 3;
				r31 = 0;
			}
			b43legacy_radio_write16(dev, 0x43, i - 9);
			/* FIXME: shouldn't txctl1 be zero in the next line
			 * and 3 in the loop above? */
			b43legacy_radio_write16(dev, 0x52,
					      phy->txctl2
					      | (3/*txctl1*/ << 4));
			udelay(10);
			b43legacy_voluntary_preempt();

			b43legacy_phy_set_baseband_attenuation(dev, j * 2);

			tmp = (regstack[10] & 0xFFF0);
			if (r31)
				tmp |= 0x0008;
			b43legacy_radio_write16(dev, 0x7A, tmp);

			tmp_control = b43legacy_get_lopair(phy, i, j * 2);
			b43legacy_phy_lo_g_state(dev, &control, tmp_control,
						 r27);
		}
	}

	/* Restoration */
	if (phy->gmode) {
		b43legacy_phy_write(dev, 0x0015, 0xE300);
		b43legacy_phy_write(dev, 0x0812, (r27 << 8) | 0xA0);
		udelay(5);
		b43legacy_phy_write(dev, 0x0812, (r27 << 8) | 0xA2);
		udelay(2);
		b43legacy_phy_write(dev, 0x0812, (r27 << 8) | 0xA3);
		b43legacy_voluntary_preempt();
	} else
		b43legacy_phy_write(dev, 0x0015, r27 | 0xEFA0);
	b43legacy_phy_lo_adjust(dev, is_initializing);
	b43legacy_phy_write(dev, 0x002E, 0x807F);
	if (phy->gmode)
		b43legacy_phy_write(dev, 0x002F, 0x0202);
	else
		b43legacy_phy_write(dev, 0x002F, 0x0101);
	b43legacy_write16(dev, B43legacy_MMIO_CHANNEL_EXT, regstack[4]);
	b43legacy_phy_write(dev, 0x0015, regstack[5]);
	b43legacy_phy_write(dev, 0x002A, regstack[6]);
	b43legacy_phy_write(dev, 0x0035, regstack[7]);
	b43legacy_phy_write(dev, 0x0060, regstack[8]);
	b43legacy_radio_write16(dev, 0x0043, regstack[9]);
	b43legacy_radio_write16(dev, 0x007A, regstack[10]);
	regstack[11] &= 0x00F0;
	regstack[11] |= (b43legacy_radio_read16(dev, 0x52) & 0x000F);
	b43legacy_radio_write16(dev, 0x52, regstack[11]);
	b43legacy_write16(dev, 0x03E2, regstack[3]);
	if (phy->gmode) {
		b43legacy_phy_write(dev, 0x0811, regstack[12]);
		b43legacy_phy_write(dev, 0x0812, regstack[13]);
		b43legacy_phy_write(dev, 0x0814, regstack[14]);
		b43legacy_phy_write(dev, 0x0815, regstack[15]);
		b43legacy_phy_write(dev, B43legacy_PHY_G_CRS, regstack[0]);
		b43legacy_phy_write(dev, 0x0802, regstack[1]);
	}
	b43legacy_radio_selectchannel(dev, oldchannel, 1);

#ifdef CONFIG_B43LEGACY_DEBUG
	{
		/* Sanity check for all lopairs. */
		for (i = 0; i < B43legacy_LO_COUNT; i++) {
			tmp_control = phy->_lo_pairs + i;
			if (tmp_control->low < -8 || tmp_control->low > 8 ||
			    tmp_control->high < -8 || tmp_control->high > 8)
				b43legacywarn(dev->wl,
				       "WARNING: Invalid LOpair (low: %d, high:"
				       " %d, index: %d)\n",
				       tmp_control->low, tmp_control->high, i);
		}
	}
#endif /* CONFIG_B43LEGACY_DEBUG */
}