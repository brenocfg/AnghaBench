#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct matrox_pll_limits {unsigned int vcomin; } ;
struct TYPE_3__ {unsigned int ref_freq; } ;
struct TYPE_4__ {TYPE_1__ pll; } ;
struct matrox_fb_info {TYPE_2__ features; } ;

/* Variables and functions */
 unsigned int NO_MORE_MNP ; 

__attribute__((used)) static unsigned int g450_nextpll(const struct matrox_fb_info *minfo,
				 const struct matrox_pll_limits *pi,
				 unsigned int *fvco, unsigned int mnp)
{
	unsigned int m, n, p;
	unsigned int tvco = *fvco;

	m = (mnp >> 16) & 0xFF;
	p = mnp & 0xFF;

	do {
		if (m == 0 || m == 0xFF) {
			if (m == 0) {
				if (p & 0x40) {
					return NO_MORE_MNP;
				}
			        if (p & 3) {
					p--;
				} else {
					p = 0x40;
				}
				tvco >>= 1;
				if (tvco < pi->vcomin) {
					return NO_MORE_MNP;
				}
				*fvco = tvco;
			}

			p &= 0x43;
			if (tvco < 550000) {
/*				p |= 0x00; */
			} else if (tvco < 700000) {
				p |= 0x08;
			} else if (tvco < 1000000) {
				p |= 0x10;
			} else if (tvco < 1150000) {
				p |= 0x18;
			} else {
				p |= 0x20;
			}
			m = 9;
		} else {
			m--;
		}
		n = ((tvco * (m+1) + minfo->features.pll.ref_freq) / (minfo->features.pll.ref_freq * 2)) - 2;
	} while (n < 0x03 || n > 0x7A);
	return (m << 16) | (n << 8) | p;
}