#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_7__ {int crystalfreq; } ;
struct TYPE_8__ {TYPE_3__ pmu; } ;
struct ssb_bus {TYPE_4__ chipco; } ;
struct b43_wldev {TYPE_2__* dev; } ;
struct b206x_channel {unsigned int channel; int* data; int freq; } ;
struct TYPE_6__ {TYPE_1__* sdev; } ;
struct TYPE_5__ {struct ssb_bus* bus; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct b206x_channel*) ; 
 int /*<<< orphan*/  B2063_A_RX_1ST3 ; 
 int /*<<< orphan*/  B2063_A_RX_2ND1 ; 
 int /*<<< orphan*/  B2063_A_RX_2ND4 ; 
 int /*<<< orphan*/  B2063_A_RX_2ND7 ; 
 int /*<<< orphan*/  B2063_A_RX_PS6 ; 
 int /*<<< orphan*/  B2063_COMM15 ; 
 int /*<<< orphan*/  B2063_LOGEN_BUF2 ; 
 int /*<<< orphan*/  B2063_LOGEN_MIXER2 ; 
 int /*<<< orphan*/  B2063_LOGEN_RCCR1 ; 
 int /*<<< orphan*/  B2063_LOGEN_VCOBUF1 ; 
 int /*<<< orphan*/  B2063_PA_CTL11 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_CP2 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_CP3 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_LF1 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_LF2 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_LF3 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_LF4 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_SG1 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_SG2 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_SG3 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_SG4 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_VCO1 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_VCO_CALIB3 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_VCO_CALIB5 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_VCO_CALIB6 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_VCO_CALIB7 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_VCO_CALIB8 ; 
 int /*<<< orphan*/  B2063_PLL_JTAG_PLL_XTAL_12 ; 
 int /*<<< orphan*/  B2063_PLL_SP2 ; 
 int /*<<< orphan*/  B2063_TX_RF_CTL2 ; 
 int /*<<< orphan*/  B2063_TX_RF_CTL5 ; 
 scalar_t__ B43_WARN_ON (int) ; 
 int EINVAL ; 
 struct b206x_channel* b2063_chantbl ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_radio_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpphy_b2063_vco_calib (struct b43_wldev*) ; 
 int lpphy_qdiv_roundup (int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int lpphy_b2063_tune(struct b43_wldev *dev,
			    unsigned int channel)
{
	struct ssb_bus *bus = dev->dev->sdev->bus;

	static const struct b206x_channel *chandata = NULL;
	u32 crystal_freq = bus->chipco.pmu.crystalfreq * 1000;
	u32 freqref, vco_freq, val1, val2, val3, timeout, timeoutref, count;
	u16 old_comm15, scale;
	u32 tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
	int i, div = (crystal_freq <= 26000000 ? 1 : 2);

	for (i = 0; i < ARRAY_SIZE(b2063_chantbl); i++) {
		if (b2063_chantbl[i].channel == channel) {
			chandata = &b2063_chantbl[i];
			break;
		}
	}

	if (B43_WARN_ON(!chandata))
		return -EINVAL;

	b43_radio_write(dev, B2063_LOGEN_VCOBUF1, chandata->data[0]);
	b43_radio_write(dev, B2063_LOGEN_MIXER2, chandata->data[1]);
	b43_radio_write(dev, B2063_LOGEN_BUF2, chandata->data[2]);
	b43_radio_write(dev, B2063_LOGEN_RCCR1, chandata->data[3]);
	b43_radio_write(dev, B2063_A_RX_1ST3, chandata->data[4]);
	b43_radio_write(dev, B2063_A_RX_2ND1, chandata->data[5]);
	b43_radio_write(dev, B2063_A_RX_2ND4, chandata->data[6]);
	b43_radio_write(dev, B2063_A_RX_2ND7, chandata->data[7]);
	b43_radio_write(dev, B2063_A_RX_PS6, chandata->data[8]);
	b43_radio_write(dev, B2063_TX_RF_CTL2, chandata->data[9]);
	b43_radio_write(dev, B2063_TX_RF_CTL5, chandata->data[10]);
	b43_radio_write(dev, B2063_PA_CTL11, chandata->data[11]);

	old_comm15 = b43_radio_read(dev, B2063_COMM15);
	b43_radio_set(dev, B2063_COMM15, 0x1E);

	if (chandata->freq > 4000) /* spec says 2484, but 4000 is safer */
		vco_freq = chandata->freq << 1;
	else
		vco_freq = chandata->freq << 2;

	freqref = crystal_freq * 3;
	val1 = lpphy_qdiv_roundup(crystal_freq, 1000000, 16);
	val2 = lpphy_qdiv_roundup(crystal_freq, 1000000 * div, 16);
	val3 = lpphy_qdiv_roundup(vco_freq, 3, 16);
	timeout = ((((8 * crystal_freq) / (div * 5000000)) + 1) >> 1) - 1;
	b43_radio_write(dev, B2063_PLL_JTAG_PLL_VCO_CALIB3, 0x2);
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_VCO_CALIB6,
			  0xFFF8, timeout >> 2);
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_VCO_CALIB7,
			  0xFF9F,timeout << 5);

	timeoutref = ((((8 * crystal_freq) / (div * (timeout + 1))) +
						999999) / 1000000) + 1;
	b43_radio_write(dev, B2063_PLL_JTAG_PLL_VCO_CALIB5, timeoutref);

	count = lpphy_qdiv_roundup(val3, val2 + 16, 16);
	count *= (timeout + 1) * (timeoutref + 1);
	count--;
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_VCO_CALIB7,
						0xF0, count >> 8);
	b43_radio_write(dev, B2063_PLL_JTAG_PLL_VCO_CALIB8, count & 0xFF);

	tmp1 = ((val3 * 62500) / freqref) << 4;
	tmp2 = ((val3 * 62500) % freqref) << 4;
	while (tmp2 >= freqref) {
		tmp1++;
		tmp2 -= freqref;
	}
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_SG1, 0xFFE0, tmp1 >> 4);
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_SG2, 0xFE0F, tmp1 << 4);
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_SG2, 0xFFF0, tmp1 >> 16);
	b43_radio_write(dev, B2063_PLL_JTAG_PLL_SG3, (tmp2 >> 8) & 0xFF);
	b43_radio_write(dev, B2063_PLL_JTAG_PLL_SG4, tmp2 & 0xFF);

	b43_radio_write(dev, B2063_PLL_JTAG_PLL_LF1, 0xB9);
	b43_radio_write(dev, B2063_PLL_JTAG_PLL_LF2, 0x88);
	b43_radio_write(dev, B2063_PLL_JTAG_PLL_LF3, 0x28);
	b43_radio_write(dev, B2063_PLL_JTAG_PLL_LF4, 0x63);

	tmp3 = ((41 * (val3 - 3000)) /1200) + 27;
	tmp4 = lpphy_qdiv_roundup(132000 * tmp1, 8451, 16);

	if ((tmp4 + tmp3 - 1) / tmp3 > 60) {
		scale = 1;
		tmp5 = ((tmp4 + tmp3) / (tmp3 << 1)) - 8;
	} else {
		scale = 0;
		tmp5 = ((tmp4 + (tmp3 >> 1)) / tmp3) - 8;
	}
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_CP2, 0xFFC0, tmp5);
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_CP2, 0xFFBF, scale << 6);

	tmp6 = lpphy_qdiv_roundup(100 * val1, val3, 16);
	tmp6 *= (tmp5 * 8) * (scale + 1);
	if (tmp6 > 150)
		tmp6 = 0;

	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_CP3, 0xFFE0, tmp6);
	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_CP3, 0xFFDF, scale << 5);

	b43_radio_maskset(dev, B2063_PLL_JTAG_PLL_XTAL_12, 0xFFFB, 0x4);
	if (crystal_freq > 26000000)
		b43_radio_set(dev, B2063_PLL_JTAG_PLL_XTAL_12, 0x2);
	else
		b43_radio_mask(dev, B2063_PLL_JTAG_PLL_XTAL_12, 0xFD);

	if (val1 == 45)
		b43_radio_set(dev, B2063_PLL_JTAG_PLL_VCO1, 0x2);
	else
		b43_radio_mask(dev, B2063_PLL_JTAG_PLL_VCO1, 0xFD);

	b43_radio_set(dev, B2063_PLL_SP2, 0x3);
	udelay(1);
	b43_radio_mask(dev, B2063_PLL_SP2, 0xFFFC);
	lpphy_b2063_vco_calib(dev);
	b43_radio_write(dev, B2063_COMM15, old_comm15);

	return 0;
}