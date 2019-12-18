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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ is_40mhz; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__ phy; } ;
struct b43_c32 {int q; int i; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_BBCFG ; 
 int B43_NPHY_BBCFG_RSTRX ; 
 void* CORDIC_CONVERT (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct b43_c32 b43_cordic (int) ; 
 int b43_nphy_load_samples (struct b43_wldev*,struct b43_c32*,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 struct b43_c32* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct b43_c32*) ; 

__attribute__((used)) static u16 b43_nphy_gen_load_samples(struct b43_wldev *dev, u32 freq, u16 max,
					bool test)
{
	int i;
	u16 bw, len, rot, angle;
	struct b43_c32 *samples;


	bw = (dev->phy.is_40mhz) ? 40 : 20;
	len = bw << 3;

	if (test) {
		if (b43_phy_read(dev, B43_NPHY_BBCFG) & B43_NPHY_BBCFG_RSTRX)
			bw = 82;
		else
			bw = 80;

		if (dev->phy.is_40mhz)
			bw <<= 1;

		len = bw << 1;
	}

	samples = kcalloc(len, sizeof(struct b43_c32), GFP_KERNEL);
	if (!samples) {
		b43err(dev->wl, "allocation for samples generation failed\n");
		return 0;
	}
	rot = (((freq * 36) / bw) << 16) / 100;
	angle = 0;

	for (i = 0; i < len; i++) {
		samples[i] = b43_cordic(angle);
		angle += rot;
		samples[i].q = CORDIC_CONVERT(samples[i].q * max);
		samples[i].i = CORDIC_CONVERT(samples[i].i * max);
	}

	i = b43_nphy_load_samples(dev, samples, len);
	kfree(samples);
	return (i < 0) ? 0 : len;
}