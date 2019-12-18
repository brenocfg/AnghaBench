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
struct hw_data {int dummy; } ;

/* Variables and functions */
 int MASK_CALIB_START ; 
 int MASK_IQCAL_MODE ; 
 int MASK_IQCAL_TONE_SEL ; 
 int /*<<< orphan*/  PHY_DEBUG (char*) ; 
 int REG_MODE_CTRL ; 
 int /*<<< orphan*/  _rx_iq_calibration_winbond (struct hw_data*,int) ; 
 int /*<<< orphan*/  _rxadc_dc_offset_cancellation_winbond (struct hw_data*,int) ; 
 int /*<<< orphan*/  _tx_iq_calibration_winbond (struct hw_data*) ; 
 int /*<<< orphan*/  hw_get_cxx_reg (struct hw_data*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw_get_dxx_reg (struct hw_data*,int,int*) ; 
 int /*<<< orphan*/  hw_set_cxx_reg (struct hw_data*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_set_dxx_reg (struct hw_data*,int,int) ; 
 int /*<<< orphan*/  mac_ctrl ; 
 int /*<<< orphan*/  phy_init_rf (struct hw_data*) ; 
 int /*<<< orphan*/  rf_ctrl ; 

void phy_calibration_winbond(struct hw_data *phw_data, u32 frequency)
{
	u32     reg_mode_ctrl;
	u32     iq_alpha;

	PHY_DEBUG(("[CAL] -> phy_calibration_winbond()\n"));

	// 20040701 1.1.25.1000 kevin
	hw_get_cxx_reg(phw_data, 0x80, &mac_ctrl);
	hw_get_cxx_reg(phw_data, 0xE4, &rf_ctrl);
	hw_get_dxx_reg(phw_data, 0x58, &iq_alpha);



	_rxadc_dc_offset_cancellation_winbond(phw_data, frequency);
	//_txidac_dc_offset_cancellation_winbond(phw_data);
	//_txqdac_dc_offset_cacellation_winbond(phw_data);

	_tx_iq_calibration_winbond(phw_data);
	_rx_iq_calibration_winbond(phw_data, frequency);

	//------------------------------------------------------------------------
	hw_get_dxx_reg(phw_data, REG_MODE_CTRL, &reg_mode_ctrl);
	reg_mode_ctrl &= ~(MASK_IQCAL_TONE_SEL|MASK_IQCAL_MODE|MASK_CALIB_START); // set when finish
	hw_set_dxx_reg(phw_data, REG_MODE_CTRL, reg_mode_ctrl);
	PHY_DEBUG(("[CAL]    MODE_CTRL (write) = 0x%08X\n", reg_mode_ctrl));

	// i. Set RFIC to "Normal mode"
	hw_set_cxx_reg(phw_data, 0x80, mac_ctrl);
	hw_set_cxx_reg(phw_data, 0xE4, rf_ctrl);
	hw_set_dxx_reg(phw_data, 0x58, iq_alpha);


	//------------------------------------------------------------------------
	phy_init_rf(phw_data);

}