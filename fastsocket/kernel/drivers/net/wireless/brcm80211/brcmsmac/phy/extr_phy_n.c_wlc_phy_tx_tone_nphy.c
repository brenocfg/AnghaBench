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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int EBADE ; 
 scalar_t__ wlc_phy_gen_load_samples_nphy (struct brcms_phy*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_runsamples_nphy (struct brcms_phy*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
wlc_phy_tx_tone_nphy(struct brcms_phy *pi, u32 f_kHz, u16 max_val,
		     u8 iqmode, u8 dac_test_mode, bool modify_bbmult)
{
	u16 num_samps;
	u16 loops = 0xffff;
	u16 wait = 0;

	num_samps = wlc_phy_gen_load_samples_nphy(pi, f_kHz, max_val,
						  dac_test_mode);
	if (num_samps == 0)
		return -EBADE;

	wlc_phy_runsamples_nphy(pi, num_samps, loops, wait, iqmode,
				dac_test_mode, modify_bbmult);

	return 0;
}