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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct hw_data {int txvga_setting_for_cal; int revision; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_DEBUG (char*) ; 
 int /*<<< orphan*/  _reset_rx_cal (struct hw_data*) ; 
 scalar_t__ _rx_iq_calibration_loop_winbond (struct hw_data*,int,int) ; 
 int /*<<< orphan*/  _s4_to_s32 (int) ; 
 int /*<<< orphan*/  _s5_to_s32 (int) ; 
 int /*<<< orphan*/  _s6_to_s32 (int) ; 
 int /*<<< orphan*/  hw_get_dxx_reg (struct hw_data*,int,int*) ; 
 int /*<<< orphan*/  phy_set_rf_data (struct hw_data*,int,int) ; 

void _rx_iq_calibration_winbond(struct hw_data *phw_data, u32 frequency)
{
// figo 20050523 marked thsi flag for can't compile for relesase
#ifdef _DEBUG
	s32     rx_cal_reg[4];
	u32     val;
#endif

	u8      result;

	PHY_DEBUG(("[CAL] -> [5]_rx_iq_calibration()\n"));
// a. Set RFIC to "RX calibration mode"
	//; ----- Calibration (7). RX path IQ imbalance calibration loop
	//	0x01 0xFFBFC2  ; 3FEFF  ; Calibration (7a). enable RX IQ calibration loop circuits
	phy_set_rf_data(phw_data, 1, (1<<24)|0xEFBFC2);
	//	0x0B 0x1A01D6  ; 06817  ; Calibration (7b). enable RX I/Q cal loop SW1 circuit
	phy_set_rf_data(phw_data, 11, (11<<24)|0x1A05D6);
	//0x05 0x24848A  ; 09212  ; Calibration (7c). setting TX-VGA gain (TXGCH) to 2 --> to be optimized
	phy_set_rf_data(phw_data, 5, (5<<24)| phw_data->txvga_setting_for_cal);
	//0x06 0x06840C  ; 01A10  ; Calibration (7d). RXGCH=00; RXGCL=010 000 (RXVGA) --> to be optimized
	phy_set_rf_data(phw_data, 6, (6<<24)|0x06834C);
	//0x00 0xFFF1C0  ; 3F7C7  ; Calibration (7e). turn on IQ imbalance/Test mode
	phy_set_rf_data(phw_data, 0, (0<<24)|0xFFF1C0);

	//  ; [BB-chip]: Calibration (7f). Send test pattern
	//	; [BB-chip]: Calibration (7g). Search RXGCL optimal value
	//	; [BB-chip]: Calibration (7h). Caculate RX-path IQ imbalance and setting RX path IQ compensation table

	result = _rx_iq_calibration_loop_winbond(phw_data, 12589, frequency);

	if (result > 0)
	{
		_reset_rx_cal(phw_data);
		result = _rx_iq_calibration_loop_winbond(phw_data, 7943, frequency);

		if (result > 0)
		{
			_reset_rx_cal(phw_data);
			result = _rx_iq_calibration_loop_winbond(phw_data, 5011, frequency);

			if (result > 0)
			{
				PHY_DEBUG(("[CAL] ** <_rx_iq_calibration> **************\n"));
				PHY_DEBUG(("[CAL] ** RX_IQ_CALIBRATION FAILURE !!\n"));
				PHY_DEBUG(("[CAL] **************************************\n"));
				_reset_rx_cal(phw_data);
			}
		}
	}

#ifdef _DEBUG
	hw_get_dxx_reg(phw_data, 0x54, &val);
	PHY_DEBUG(("[CAL]    ** 0x54 = 0x%08X\n", val));

	if (phw_data->revision == 0x2002) // 1st-cut
	{
		rx_cal_reg[0] = _s4_to_s32((val & 0x0000F000) >> 12);
		rx_cal_reg[1] = _s4_to_s32((val & 0x00000F00) >>  8);
		rx_cal_reg[2] = _s4_to_s32((val & 0x000000F0) >>  4);
		rx_cal_reg[3] = _s4_to_s32((val & 0x0000000F));
	}
	else // 2nd-cut
	{
		rx_cal_reg[0] = _s5_to_s32((val & 0xF8000000) >> 27);
		rx_cal_reg[1] = _s6_to_s32((val & 0x07E00000) >> 21);
		rx_cal_reg[2] = _s6_to_s32((val & 0x001F8000) >> 15);
		rx_cal_reg[3] = _s5_to_s32((val & 0x00007C00) >> 10);
	}

	PHY_DEBUG(("[CAL]    ** rx_cal_reg[0] = %d\n", rx_cal_reg[0]));
	PHY_DEBUG(("[CAL]       rx_cal_reg[1] = %d\n", rx_cal_reg[1]));
	PHY_DEBUG(("[CAL]       rx_cal_reg[2] = %d\n", rx_cal_reg[2]));
	PHY_DEBUG(("[CAL]       rx_cal_reg[3] = %d\n", rx_cal_reg[3]));
#endif

}