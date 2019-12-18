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
struct net_device {int dummy; } ;
struct dscc4_dev_priv {int /*<<< orphan*/  dev_id; TYPE_1__* pci_priv; } ;
struct TYPE_2__ {int xtal_hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRR ; 
 int BRR_DIVIDER_MAX ; 
 int Ccr0ClockMask ; 
 scalar_t__ dscc4_check_clock_ability (int /*<<< orphan*/ ) ; 
 struct dscc4_dev_priv* dscc4_priv (struct net_device*) ; 
 int /*<<< orphan*/  scc_writel (int,struct dscc4_dev_priv*,struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dscc4_set_clock(struct net_device *dev, u32 *bps, u32 *state)
{
	struct dscc4_dev_priv *dpriv = dscc4_priv(dev);
	int ret = -1;
	u32 brr;

	*state &= ~Ccr0ClockMask;
	if (*bps) { /* Clock generated - required for DCE */
		u32 n = 0, m = 0, divider;
		int xtal;

		xtal = dpriv->pci_priv->xtal_hz;
		if (!xtal)
			goto done;
		if (dscc4_check_clock_ability(dpriv->dev_id) < 0)
			goto done;
		divider = xtal / *bps;
		if (divider > BRR_DIVIDER_MAX) {
			divider >>= 4;
			*state |= 0x00000036; /* Clock mode 6b (BRG/16) */
		} else
			*state |= 0x00000037; /* Clock mode 7b (BRG) */
		if (divider >> 22) {
			n = 63;
			m = 15;
		} else if (divider) {
			/* Extraction of the 6 highest weighted bits */
			m = 0;
			while (0xffffffc0 & divider) {
				m++;
				divider >>= 1;
			}
			n = divider;
		}
		brr = (m << 8) | n;
		divider = n << m;
		if (!(*state & 0x00000001)) /* ?b mode mask => clock mode 6b */
			divider <<= 4;
		*bps = xtal / divider;
	} else {
		/*
		 * External clock - DTE
		 * "state" already reflects Clock mode 0a (CCR0 = 0xzzzzzz00).
		 * Nothing more to be done
		 */
		brr = 0;
	}
	scc_writel(brr, dpriv, dev, BRR);
	ret = 0;
done:
	return ret;
}