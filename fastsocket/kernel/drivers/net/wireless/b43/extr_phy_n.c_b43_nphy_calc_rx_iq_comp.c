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
typedef  int u32 ;
typedef  int u16 ;
struct nphy_iq_est {int iq0_prod; int i0_pwr; int q0_pwr; int iq1_prod; int i1_pwr; int q1_pwr; } ;
struct TYPE_2__ {int rev; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_n_iq_comp {int a0; int b0; int a1; int b1; } ;
typedef  int s32 ;

/* Variables and functions */
 int abs (int) ; 
 int /*<<< orphan*/  b43_nphy_rx_iq_coeffs (struct b43_wldev*,int,struct b43_phy_n_iq_comp*) ; 
 int /*<<< orphan*/  b43_nphy_rx_iq_est (struct b43_wldev*,struct nphy_iq_est*,int,int,int) ; 
 int fls (int) ; 
 int int_sqrt (int) ; 

__attribute__((used)) static void b43_nphy_calc_rx_iq_comp(struct b43_wldev *dev, u8 mask)
{
	int i;
	s32 iq;
	u32 ii;
	u32 qq;
	int iq_nbits, qq_nbits;
	int arsh, brsh;
	u16 tmp, a, b;

	struct nphy_iq_est est;
	struct b43_phy_n_iq_comp old;
	struct b43_phy_n_iq_comp new = { };
	bool error = false;

	if (mask == 0)
		return;

	b43_nphy_rx_iq_coeffs(dev, false, &old);
	b43_nphy_rx_iq_coeffs(dev, true, &new);
	b43_nphy_rx_iq_est(dev, &est, 0x4000, 32, false);
	new = old;

	for (i = 0; i < 2; i++) {
		if (i == 0 && (mask & 1)) {
			iq = est.iq0_prod;
			ii = est.i0_pwr;
			qq = est.q0_pwr;
		} else if (i == 1 && (mask & 2)) {
			iq = est.iq1_prod;
			ii = est.i1_pwr;
			qq = est.q1_pwr;
		} else {
			continue;
		}

		if (ii + qq < 2) {
			error = true;
			break;
		}

		iq_nbits = fls(abs(iq));
		qq_nbits = fls(qq);

		arsh = iq_nbits - 20;
		if (arsh >= 0) {
			a = -((iq << (30 - iq_nbits)) + (ii >> (1 + arsh)));
			tmp = ii >> arsh;
		} else {
			a = -((iq << (30 - iq_nbits)) + (ii << (-1 - arsh)));
			tmp = ii << -arsh;
		}
		if (tmp == 0) {
			error = true;
			break;
		}
		a /= tmp;

		brsh = qq_nbits - 11;
		if (brsh >= 0) {
			b = (qq << (31 - qq_nbits));
			tmp = ii >> brsh;
		} else {
			b = (qq << (31 - qq_nbits));
			tmp = ii << -brsh;
		}
		if (tmp == 0) {
			error = true;
			break;
		}
		b = int_sqrt(b / tmp - a * a) - (1 << 10);

		if (i == 0 && (mask & 0x1)) {
			if (dev->phy.rev >= 3) {
				new.a0 = a & 0x3FF;
				new.b0 = b & 0x3FF;
			} else {
				new.a0 = b & 0x3FF;
				new.b0 = a & 0x3FF;
			}
		} else if (i == 1 && (mask & 0x2)) {
			if (dev->phy.rev >= 3) {
				new.a1 = a & 0x3FF;
				new.b1 = b & 0x3FF;
			} else {
				new.a1 = b & 0x3FF;
				new.b1 = a & 0x3FF;
			}
		}
	}

	if (error)
		new = old;

	b43_nphy_rx_iq_coeffs(dev, true, &new);
}