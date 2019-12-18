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
typedef  int u32 ;
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_RTTBCNRC ; 
 int E1000_RTTBCNRC_RF_DEC_MASK ; 
 int E1000_RTTBCNRC_RF_INT_MASK ; 
 int E1000_RTTBCNRC_RF_INT_SHIFT ; 
 int E1000_RTTBCNRC_RS_ENA ; 
 int /*<<< orphan*/  E1000_RTTBCNRM ; 
 int /*<<< orphan*/  E1000_RTTDQSEL ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void igb_set_vf_rate_limit(struct e1000_hw *hw, int vf, int tx_rate,
				  int link_speed)
{
	int rf_dec, rf_int;
	u32 bcnrc_val;

	if (tx_rate != 0) {
		/* Calculate the rate factor values to set */
		rf_int = link_speed / tx_rate;
		rf_dec = (link_speed - (rf_int * tx_rate));
		rf_dec = (rf_dec * (1 << E1000_RTTBCNRC_RF_INT_SHIFT)) /
			 tx_rate;

		bcnrc_val = E1000_RTTBCNRC_RS_ENA;
		bcnrc_val |= ((rf_int << E1000_RTTBCNRC_RF_INT_SHIFT) &
			      E1000_RTTBCNRC_RF_INT_MASK);
		bcnrc_val |= (rf_dec & E1000_RTTBCNRC_RF_DEC_MASK);
	} else {
		bcnrc_val = 0;
	}

	wr32(E1000_RTTDQSEL, vf); /* vf X uses queue X */
	/* Set global transmit compensation time to the MMW_SIZE in RTTBCNRM
	 * register. MMW_SIZE=0x014 if 9728-byte jumbo is supported.
	 */
	wr32(E1000_RTTBCNRM, 0x14);
	wr32(E1000_RTTBCNRC, bcnrc_val);
}