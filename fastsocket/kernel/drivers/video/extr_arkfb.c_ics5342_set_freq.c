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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct dac_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ mode; } ;

/* Variables and functions */
 TYPE_1__* DAC_PAR (struct dac_info*) ; 
 scalar_t__ DAC_PSEUDO8_16 ; 
 int EINVAL ; 
 int /*<<< orphan*/  dac_write_regs (struct dac_info*,int*,int) ; 
 int /*<<< orphan*/  ics5342_pll ; 
 int /*<<< orphan*/  ics5342_pll_pd4 ; 
 int svga_compute_pll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ics5342_set_freq(struct dac_info *info, int channel, u32 freq)
{
	u16 m, n, r;

	/* only postdivider 4 (r=2) is valid in mode DAC_PSEUDO8_16 */
	int rv = svga_compute_pll((DAC_PAR(info)->mode == DAC_PSEUDO8_16)
				  ? &ics5342_pll_pd4 : &ics5342_pll,
				  freq, &m, &n, &r, 0);

	if (rv < 0) {
		return -EINVAL;
	} else {
		u8 code[6] = {4, 3, 5, m-2, 5, (n-2) | (r << 5)};
		dac_write_regs(info, code, 3);
		return 0;
	}
}