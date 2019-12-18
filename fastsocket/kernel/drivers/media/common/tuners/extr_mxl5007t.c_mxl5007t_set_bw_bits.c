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
struct mxl5007t_state {int /*<<< orphan*/  tab_rftune; } ;
typedef  enum mxl5007t_bw_mhz { ____Placeholder_mxl5007t_bw_mhz } mxl5007t_bw_mhz ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
#define  MxL_BW_6MHz 130 
#define  MxL_BW_7MHz 129 
#define  MxL_BW_8MHz 128 
 int /*<<< orphan*/  mxl_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_reg_bits (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void mxl5007t_set_bw_bits(struct mxl5007t_state *state,
				 enum mxl5007t_bw_mhz bw)
{
	u8 val;

	switch (bw) {
	case MxL_BW_6MHz:
		val = 0x15; /* set DIG_MODEINDEX, DIG_MODEINDEX_A,
			     * and DIG_MODEINDEX_CSF */
		break;
	case MxL_BW_7MHz:
		val = 0x2a;
		break;
	case MxL_BW_8MHz:
		val = 0x3f;
		break;
	default:
		mxl_fail(-EINVAL);
		return;
	}
	set_reg_bits(state->tab_rftune, 0x0c, 0x3f, val);

	return;
}