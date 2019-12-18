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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct brcms_c_info {TYPE_1__* stf; } ;
struct TYPE_2__ {int phytxant; int txchain; scalar_t__ txant; } ;

/* Variables and functions */
 scalar_t__ ANT_TX_DEF ; 
 scalar_t__ PHY_TXC1_MODE_SISO ; 
 int PHY_TXC_ANT_MASK ; 
 int PHY_TXC_ANT_SHIFT ; 
 scalar_t__ rspec_stf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 _brcms_c_stf_phytxchain_sel(struct brcms_c_info *wlc,
				       u32 rspec)
{
	u16 phytxant = wlc->stf->phytxant;

	if (rspec_stf(rspec) != PHY_TXC1_MODE_SISO)
		phytxant = wlc->stf->txchain << PHY_TXC_ANT_SHIFT;
	else if (wlc->stf->txant == ANT_TX_DEF)
		phytxant = wlc->stf->txchain << PHY_TXC_ANT_SHIFT;
	phytxant &= PHY_TXC_ANT_MASK;
	return phytxant;
}