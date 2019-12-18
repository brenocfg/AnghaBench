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
struct b43_wldev {int /*<<< orphan*/  wl; } ;
typedef  enum b43_nphy_rf_sequence { ____Placeholder_b43_nphy_rf_sequence } b43_nphy_rf_sequence ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  B43_NPHY_RFSEQMODE ; 
 int const B43_NPHY_RFSEQMODE_CAOVER ; 
 int const B43_NPHY_RFSEQMODE_TROVER ; 
 int /*<<< orphan*/  B43_NPHY_RFSEQST ; 
 int /*<<< orphan*/  B43_NPHY_RFSEQTR ; 
#define  B43_NPHY_RFSEQTR_RST2RX 139 
#define  B43_NPHY_RFSEQTR_RX2TX 138 
#define  B43_NPHY_RFSEQTR_TX2RX 137 
#define  B43_NPHY_RFSEQTR_UPGH 136 
#define  B43_NPHY_RFSEQTR_UPGL 135 
#define  B43_NPHY_RFSEQTR_UPGU 134 
#define  B43_RFSEQ_RESET2RX 133 
#define  B43_RFSEQ_RX2TX 132 
#define  B43_RFSEQ_TX2RX 131 
#define  B43_RFSEQ_UPDATE_GAINH 130 
#define  B43_RFSEQ_UPDATE_GAINL 129 
#define  B43_RFSEQ_UPDATE_GAINU 128 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int const b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void b43_nphy_force_rf_sequence(struct b43_wldev *dev,
				       enum b43_nphy_rf_sequence seq)
{
	static const u16 trigger[] = {
		[B43_RFSEQ_RX2TX]		= B43_NPHY_RFSEQTR_RX2TX,
		[B43_RFSEQ_TX2RX]		= B43_NPHY_RFSEQTR_TX2RX,
		[B43_RFSEQ_RESET2RX]		= B43_NPHY_RFSEQTR_RST2RX,
		[B43_RFSEQ_UPDATE_GAINH]	= B43_NPHY_RFSEQTR_UPGH,
		[B43_RFSEQ_UPDATE_GAINL]	= B43_NPHY_RFSEQTR_UPGL,
		[B43_RFSEQ_UPDATE_GAINU]	= B43_NPHY_RFSEQTR_UPGU,
	};
	int i;
	u16 seq_mode = b43_phy_read(dev, B43_NPHY_RFSEQMODE);

	B43_WARN_ON(seq >= ARRAY_SIZE(trigger));

	b43_phy_set(dev, B43_NPHY_RFSEQMODE,
		    B43_NPHY_RFSEQMODE_CAOVER | B43_NPHY_RFSEQMODE_TROVER);
	b43_phy_set(dev, B43_NPHY_RFSEQTR, trigger[seq]);
	for (i = 0; i < 200; i++) {
		if (!(b43_phy_read(dev, B43_NPHY_RFSEQST) & trigger[seq]))
			goto ok;
		msleep(1);
	}
	b43err(dev->wl, "RF sequence status timeout\n");
ok:
	b43_phy_write(dev, B43_NPHY_RFSEQMODE, seq_mode);
}