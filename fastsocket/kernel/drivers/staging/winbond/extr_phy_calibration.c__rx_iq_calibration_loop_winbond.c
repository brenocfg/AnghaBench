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
typedef  int u32 ;
typedef  int u16 ;
struct hw_data {int iq_rsdl_gain_tx_d2; int iq_rsdl_phase_tx_d2; int revision; } ;
typedef  int s32 ;

/* Variables and functions */
 int BIT (int) ; 
 int LOOP_TIMES ; 
 int MASK_CALIB_START ; 
 int MASK_IQCAL_MODE ; 
 int /*<<< orphan*/  PHY_DEBUG (char*) ; 
 int REG_CALIB_READ1 ; 
 int REG_CALIB_READ2 ; 
 int REG_MODE_CTRL ; 
 int _floor (int) ; 
 int _s13_to_s32 (int) ; 
 int _s32_to_s4 (int) ; 
 int _s32_to_s5 (int) ; 
 int _s32_to_s6 (int) ; 
 int _s4_to_s32 (int) ; 
 int _s5_to_s32 (int) ; 
 int _s6_to_s32 (int) ; 
 int /*<<< orphan*/  _sin_cos (int,int*,int*) ; 
 int /*<<< orphan*/  hw_get_cxx_reg (struct hw_data*,int,int*) ; 
 int /*<<< orphan*/  hw_get_dxx_reg (struct hw_data*,int,int*) ; 
 int /*<<< orphan*/  hw_set_cxx_reg (struct hw_data*,int,int) ; 
 int /*<<< orphan*/  hw_set_dxx_reg (struct hw_data*,int,int) ; 

u8 _rx_iq_calibration_loop_winbond(struct hw_data *phw_data, u16 factor, u32 frequency)
{
	u32     reg_mode_ctrl;
	s32     iqcal_tone_i;
	s32     iqcal_tone_q;
	s32     iqcal_image_i;
	s32     iqcal_image_q;
	s32     rot_tone_i_b;
	s32     rot_tone_q_b;
	s32     rot_image_i_b;
	s32     rot_image_q_b;
	s32     rx_cal_flt_b[4];
	s32     rx_cal[4];
	s32     rx_cal_reg[4];
	s32     a_2, b_2;
	s32     sin_b, sin_2b;
	s32     cos_b, cos_2b;
	s32     temp1, temp2;
	u32     val;
	u16     loop;

	u32     pwr_tone;
	u32     pwr_image;
	u8      verify_count;

	s32     iqcal_tone_i_avg,iqcal_tone_q_avg;
	s32     iqcal_image_i_avg,iqcal_image_q_avg;
	u16		capture_time;

	PHY_DEBUG(("[CAL] -> [5]_rx_iq_calibration_loop()\n"));
	PHY_DEBUG(("[CAL] ** factor = %d\n", factor));


// RF Control Override
	hw_get_cxx_reg(phw_data, 0x80, &val);
	val |= BIT(19);
	hw_set_cxx_reg(phw_data, 0x80, val);

// RF_Ctrl
	hw_get_cxx_reg(phw_data, 0xE4, &val);
	val |= BIT(0);
	hw_set_cxx_reg(phw_data, 0xE4, val);
	PHY_DEBUG(("[CAL] ** RF_CTRL(0xE4) = 0x%08X", val));

	hw_set_dxx_reg(phw_data, 0x58, 0x44444444); // IQ_Alpha

	// b.

	hw_get_dxx_reg(phw_data, REG_MODE_CTRL, &reg_mode_ctrl);
	PHY_DEBUG(("[CAL]    MODE_CTRL (read) = 0x%08X\n", reg_mode_ctrl));

	verify_count = 0;

	//for (loop = 0; loop < 1; loop++)
	//for (loop = 0; loop < LOOP_TIMES; loop++)
	loop = LOOP_TIMES;
	while (loop > 0)
	{
		PHY_DEBUG(("[CAL] [%d.] <_rx_iq_calibration_loop>\n", (LOOP_TIMES-loop+1)));
		iqcal_tone_i_avg=0;
		iqcal_tone_q_avg=0;
		iqcal_image_i_avg=0;
		iqcal_image_q_avg=0;
		capture_time=0;

		for(capture_time=0; capture_time<10; capture_time++)
		{
		// i. Set "calib_start" to 0x0
		reg_mode_ctrl &= ~MASK_CALIB_START;
		if( !hw_set_dxx_reg(phw_data, REG_MODE_CTRL, reg_mode_ctrl) )//20060718.1 modify
			return 0;
		PHY_DEBUG(("[CAL]    MODE_CTRL (write) = 0x%08X\n", reg_mode_ctrl));

		reg_mode_ctrl &= ~MASK_IQCAL_MODE;
		reg_mode_ctrl |= (MASK_CALIB_START|0x1);
		hw_set_dxx_reg(phw_data, REG_MODE_CTRL, reg_mode_ctrl);
		PHY_DEBUG(("[CAL]    MODE_CTRL (write) = 0x%08X\n", reg_mode_ctrl));

		// c.
		hw_get_dxx_reg(phw_data, REG_CALIB_READ1, &val);
		PHY_DEBUG(("[CAL]    CALIB_READ1 = 0x%08X\n", val));

		iqcal_tone_i = _s13_to_s32(val & 0x00001FFF);
		iqcal_tone_q = _s13_to_s32((val & 0x03FFE000) >> 13);
		PHY_DEBUG(("[CAL]    ** iqcal_tone_i = %d, iqcal_tone_q = %d\n",
				   iqcal_tone_i, iqcal_tone_q));

		hw_get_dxx_reg(phw_data, REG_CALIB_READ2, &val);
		PHY_DEBUG(("[CAL]    CALIB_READ2 = 0x%08X\n", val));

		iqcal_image_i = _s13_to_s32(val & 0x00001FFF);
		iqcal_image_q = _s13_to_s32((val & 0x03FFE000) >> 13);
		PHY_DEBUG(("[CAL]    ** iqcal_image_i = %d, iqcal_image_q = %d\n",
				   iqcal_image_i, iqcal_image_q));
			if( capture_time == 0)
			{
				continue;
			}
			else
			{
				iqcal_image_i_avg=( iqcal_image_i_avg*(capture_time-1) +iqcal_image_i)/capture_time;
				iqcal_image_q_avg=( iqcal_image_q_avg*(capture_time-1) +iqcal_image_q)/capture_time;
				iqcal_tone_i_avg=( iqcal_tone_i_avg*(capture_time-1) +iqcal_tone_i)/capture_time;
				iqcal_tone_q_avg=( iqcal_tone_q_avg*(capture_time-1) +iqcal_tone_q)/capture_time;
			}
		}


		iqcal_image_i = iqcal_image_i_avg;
		iqcal_image_q = iqcal_image_q_avg;
		iqcal_tone_i = iqcal_tone_i_avg;
		iqcal_tone_q = iqcal_tone_q_avg;

		// d.
		rot_tone_i_b = (iqcal_tone_i * iqcal_tone_i +
						iqcal_tone_q * iqcal_tone_q) / 1024;
		rot_tone_q_b = (iqcal_tone_i * iqcal_tone_q * (-1) +
						iqcal_tone_q * iqcal_tone_i) / 1024;
		rot_image_i_b = (iqcal_image_i * iqcal_tone_i -
						 iqcal_image_q * iqcal_tone_q) / 1024;
		rot_image_q_b = (iqcal_image_i * iqcal_tone_q +
						 iqcal_image_q * iqcal_tone_i) / 1024;

		PHY_DEBUG(("[CAL]    ** rot_tone_i_b  = %d\n", rot_tone_i_b));
		PHY_DEBUG(("[CAL]    ** rot_tone_q_b  = %d\n", rot_tone_q_b));
		PHY_DEBUG(("[CAL]    ** rot_image_i_b = %d\n", rot_image_i_b));
		PHY_DEBUG(("[CAL]    ** rot_image_q_b = %d\n", rot_image_q_b));

		// f.
		if (rot_tone_i_b == 0)
		{
			PHY_DEBUG(("[CAL] ** <_rx_iq_calibration_loop> ERROR *******\n"));
			PHY_DEBUG(("[CAL] ** rot_tone_i_b=0 to calculate EPS and THETA !!\n"));
			PHY_DEBUG(("[CAL] ******************************************\n"));
			break;
		}

		a_2 = (rot_image_i_b * 32768) / rot_tone_i_b -
			phw_data->iq_rsdl_gain_tx_d2;
		b_2 = (rot_image_q_b * 32768) / rot_tone_i_b -
			phw_data->iq_rsdl_phase_tx_d2;

		PHY_DEBUG(("[CAL]    ** iq_rsdl_gain_tx_d2 = %d\n", phw_data->iq_rsdl_gain_tx_d2));
		PHY_DEBUG(("[CAL]    ** iq_rsdl_phase_tx_d2= %d\n", phw_data->iq_rsdl_phase_tx_d2));
		PHY_DEBUG(("[CAL]    ***** EPSILON/2 = %d\n", a_2));
		PHY_DEBUG(("[CAL]    ***** THETA/2   = %d\n", b_2));

		_sin_cos(b_2, &sin_b, &cos_b);
		_sin_cos(b_2*2, &sin_2b, &cos_2b);
		PHY_DEBUG(("[CAL]    ** sin(b/2)=%d, cos(b/2)=%d\n", sin_b, cos_b));
		PHY_DEBUG(("[CAL]    ** sin(b)=%d, cos(b)=%d\n", sin_2b, cos_2b));

		if (cos_2b == 0)
		{
			PHY_DEBUG(("[CAL] ** <_rx_iq_calibration_loop> ERROR *******\n"));
			PHY_DEBUG(("[CAL] ** cos(b)=0 !!\n"));
			PHY_DEBUG(("[CAL] ******************************************\n"));
			break;
		}

		// 1280 * 32768 = 41943040
		temp1 = (41943040/cos_2b)*cos_b;

		//temp2 = (41943040/cos_2b)*sin_b*(-1);
		if (phw_data->revision == 0x2002) // 1st-cut
		{
			temp2 = (41943040/cos_2b)*sin_b*(-1);
		}
		else // 2nd-cut
		{
			temp2 = (41943040*4/cos_2b)*sin_b*(-1);
		}

		rx_cal_flt_b[0] = _floor(temp1/(32768+a_2));
		rx_cal_flt_b[1] = _floor(temp2/(32768-a_2));
		rx_cal_flt_b[2] = _floor(temp2/(32768+a_2));
		rx_cal_flt_b[3] = _floor(temp1/(32768-a_2));

		PHY_DEBUG(("[CAL]    ** rx_cal_flt_b[0] = %d\n", rx_cal_flt_b[0]));
		PHY_DEBUG(("[CAL]       rx_cal_flt_b[1] = %d\n", rx_cal_flt_b[1]));
		PHY_DEBUG(("[CAL]       rx_cal_flt_b[2] = %d\n", rx_cal_flt_b[2]));
		PHY_DEBUG(("[CAL]       rx_cal_flt_b[3] = %d\n", rx_cal_flt_b[3]));

		rx_cal[0] = rx_cal_flt_b[0] - 128;
		rx_cal[1] = rx_cal_flt_b[1];
		rx_cal[2] = rx_cal_flt_b[2];
		rx_cal[3] = rx_cal_flt_b[3] - 128;
		PHY_DEBUG(("[CAL]    ** rx_cal[0] = %d\n", rx_cal[0]));
		PHY_DEBUG(("[CAL]       rx_cal[1] = %d\n", rx_cal[1]));
		PHY_DEBUG(("[CAL]       rx_cal[2] = %d\n", rx_cal[2]));
		PHY_DEBUG(("[CAL]       rx_cal[3] = %d\n", rx_cal[3]));

		// e.
		pwr_tone = (iqcal_tone_i*iqcal_tone_i + iqcal_tone_q*iqcal_tone_q);
		pwr_image = (iqcal_image_i*iqcal_image_i + iqcal_image_q*iqcal_image_q)*factor;

		PHY_DEBUG(("[CAL]    ** pwr_tone  = %d\n", pwr_tone));
		PHY_DEBUG(("[CAL]    ** pwr_image  = %d\n", pwr_image));

		if (pwr_tone > pwr_image)
		{
			verify_count++;

			PHY_DEBUG(("[CAL] ** <_rx_iq_calibration_loop> *************\n"));
			PHY_DEBUG(("[CAL] ** VERIFY OK # %d !!\n", verify_count));
			PHY_DEBUG(("[CAL] ******************************************\n"));

			if (verify_count > 2)
			{
				PHY_DEBUG(("[CAL] ** <_rx_iq_calibration_loop> *********\n"));
				PHY_DEBUG(("[CAL] ** RX_IQ_CALIBRATION OK !!\n"));
				PHY_DEBUG(("[CAL] **************************************\n"));
				return 0;
			}

			continue;
		}
		// g.
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

		if (phw_data->revision == 0x2002) // 1st-cut
		{
			if (((rx_cal_reg[0]==7) || (rx_cal_reg[0]==(-8))) &&
				((rx_cal_reg[3]==7) || (rx_cal_reg[3]==(-8))))
			{
				PHY_DEBUG(("[CAL] ** <_rx_iq_calibration_loop> *********\n"));
				PHY_DEBUG(("[CAL] ** RX_IQ_CALIBRATION SATUATION !!\n"));
				PHY_DEBUG(("[CAL] **************************************\n"));
				break;
			}
		}
		else // 2nd-cut
		{
			if (((rx_cal_reg[0]==31) || (rx_cal_reg[0]==(-32))) &&
				((rx_cal_reg[3]==31) || (rx_cal_reg[3]==(-32))))
			{
				PHY_DEBUG(("[CAL] ** <_rx_iq_calibration_loop> *********\n"));
				PHY_DEBUG(("[CAL] ** RX_IQ_CALIBRATION SATUATION !!\n"));
				PHY_DEBUG(("[CAL] **************************************\n"));
				break;
			}
		}

		rx_cal[0] = rx_cal[0] + rx_cal_reg[0];
		rx_cal[1] = rx_cal[1] + rx_cal_reg[1];
		rx_cal[2] = rx_cal[2] + rx_cal_reg[2];
		rx_cal[3] = rx_cal[3] + rx_cal_reg[3];
		PHY_DEBUG(("[CAL]    ** apply rx_cal[0] = %d\n", rx_cal[0]));
		PHY_DEBUG(("[CAL]       apply rx_cal[1] = %d\n", rx_cal[1]));
		PHY_DEBUG(("[CAL]       apply rx_cal[2] = %d\n", rx_cal[2]));
		PHY_DEBUG(("[CAL]       apply rx_cal[3] = %d\n", rx_cal[3]));

		hw_get_dxx_reg(phw_data, 0x54, &val);
		if (phw_data->revision == 0x2002) // 1st-cut
		{
			val &= 0x0000FFFF;
			val |= ((_s32_to_s4(rx_cal[0]) << 12)|
					(_s32_to_s4(rx_cal[1]) <<  8)|
					(_s32_to_s4(rx_cal[2]) <<  4)|
					(_s32_to_s4(rx_cal[3])));
			hw_set_dxx_reg(phw_data, 0x54, val);
		}
		else // 2nd-cut
		{
			val &= 0x000003FF;
			val |= ((_s32_to_s5(rx_cal[0]) << 27)|
					(_s32_to_s6(rx_cal[1]) << 21)|
					(_s32_to_s6(rx_cal[2]) << 15)|
					(_s32_to_s5(rx_cal[3]) << 10));
			hw_set_dxx_reg(phw_data, 0x54, val);

			if( loop == 3 )
			return 0;
		}
		PHY_DEBUG(("[CAL]    ** CALIB_DATA = 0x%08X\n", val));

		loop--;
	}

	return 1;
}