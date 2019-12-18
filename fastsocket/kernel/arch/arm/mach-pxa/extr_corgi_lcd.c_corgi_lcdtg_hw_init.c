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
struct TYPE_2__ {int comadj; } ;

/* Variables and functions */
 int DEFAULT_COMADJ ; 
 int /*<<< orphan*/  PICTRL_ADRS ; 
 int PICTRL_COM_SIGNAL_OFF ; 
 int PICTRL_DAC_SIGNAL_OFF ; 
 int PICTRL_INIOFF ; 
 int PICTRL_INIT_STATE ; 
 int PICTRL_POWER_DOWN ; 
 int /*<<< orphan*/  POLCTRL_ADRS ; 
 int POLCTRL_DATA_POL_RISE ; 
 int POLCTRL_EN_ACT_H ; 
 int POLCTRL_EN_POL_RISE ; 
 int POLCTRL_SYNC_ACT_L ; 
 int POLCTRL_SYNC_POL_RISE ; 
 int POWER0_COM_DCLK ; 
 int POWER0_COM_DOUT ; 
 int POWER0_COM_OFF ; 
 int POWER0_COM_ON ; 
 int POWER0_DAC_OFF ; 
 int POWER0_DAC_ON ; 
 int POWER0_VCC5_OFF ; 
 int POWER0_VCC5_ON ; 
 int POWER1_GVSS_OFF ; 
 int POWER1_GVSS_ON ; 
 int POWER1_VDD_OFF ; 
 int POWER1_VDD_ON ; 
 int POWER1_VW_OFF ; 
 int POWER1_VW_ON ; 
 int /*<<< orphan*/  POWERREG0_ADRS ; 
 int /*<<< orphan*/  POWERREG1_ADRS ; 
 int /*<<< orphan*/  RESCTL_ADRS ; 
 int RESCTL_QVGA ; 
 int RESCTL_VGA ; 
 int /*<<< orphan*/  corgi_ssp_lcdtg_send (int /*<<< orphan*/ ,int) ; 
 int lcd_inited ; 
 int /*<<< orphan*/  lcdtg_set_common_voltage (int,int) ; 
 int /*<<< orphan*/  lcdtg_set_phadadj (int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 TYPE_1__ sharpsl_param ; 
 int /*<<< orphan*/  udelay (int) ; 

void corgi_lcdtg_hw_init(int mode)
{
	if (!lcd_inited) {
		int comadj;

		/* Initialize Internal Logic & Port */
		corgi_ssp_lcdtg_send(PICTRL_ADRS, PICTRL_POWER_DOWN | PICTRL_INIOFF | PICTRL_INIT_STATE
	  			| PICTRL_COM_SIGNAL_OFF | PICTRL_DAC_SIGNAL_OFF);

		corgi_ssp_lcdtg_send(POWERREG0_ADRS, POWER0_COM_DCLK | POWER0_COM_DOUT | POWER0_DAC_OFF
				| POWER0_COM_OFF | POWER0_VCC5_OFF);

		corgi_ssp_lcdtg_send(POWERREG1_ADRS, POWER1_VW_OFF | POWER1_GVSS_OFF | POWER1_VDD_OFF);

		/* VDD(+8V), SVSS(-4V) ON */
		corgi_ssp_lcdtg_send(POWERREG1_ADRS, POWER1_VW_OFF | POWER1_GVSS_OFF | POWER1_VDD_ON);
		mdelay(3);

		/* DAC ON */
		corgi_ssp_lcdtg_send(POWERREG0_ADRS, POWER0_COM_DCLK | POWER0_COM_DOUT | POWER0_DAC_ON
				| POWER0_COM_OFF | POWER0_VCC5_OFF);

		/* INIB = H, INI = L  */
		/* PICTL[0] = H , PICTL[1] = PICTL[2] = PICTL[4] = L */
		corgi_ssp_lcdtg_send(PICTRL_ADRS, PICTRL_INIT_STATE | PICTRL_COM_SIGNAL_OFF);

		/* Set Common Voltage */
		comadj = sharpsl_param.comadj;
		if (comadj < 0)
			comadj = DEFAULT_COMADJ;
		lcdtg_set_common_voltage((POWER0_DAC_ON | POWER0_COM_OFF | POWER0_VCC5_OFF), comadj);

		/* VCC5 ON, DAC ON */
		corgi_ssp_lcdtg_send(POWERREG0_ADRS, POWER0_COM_DCLK | POWER0_COM_DOUT | POWER0_DAC_ON |
				POWER0_COM_OFF | POWER0_VCC5_ON);

		/* GVSS(-8V) ON, VDD ON */
		corgi_ssp_lcdtg_send(POWERREG1_ADRS, POWER1_VW_OFF | POWER1_GVSS_ON | POWER1_VDD_ON);
		mdelay(2);

		/* COM SIGNAL ON (PICTL[3] = L) */
		corgi_ssp_lcdtg_send(PICTRL_ADRS, PICTRL_INIT_STATE);

		/* COM ON, DAC ON, VCC5_ON */
		corgi_ssp_lcdtg_send(POWERREG0_ADRS, POWER0_COM_DCLK | POWER0_COM_DOUT | POWER0_DAC_ON
				| POWER0_COM_ON | POWER0_VCC5_ON);

		/* VW ON, GVSS ON, VDD ON */
		corgi_ssp_lcdtg_send(POWERREG1_ADRS, POWER1_VW_ON | POWER1_GVSS_ON | POWER1_VDD_ON);

		/* Signals output enable */
		corgi_ssp_lcdtg_send(PICTRL_ADRS, 0);

		/* Set Phase Adjust */
		lcdtg_set_phadadj(mode);

		/* Initialize for Input Signals from ATI */
		corgi_ssp_lcdtg_send(POLCTRL_ADRS, POLCTRL_SYNC_POL_RISE | POLCTRL_EN_POL_RISE
				| POLCTRL_DATA_POL_RISE | POLCTRL_SYNC_ACT_L | POLCTRL_EN_ACT_H);
		udelay(1000);

		lcd_inited=1;
	} else {
		lcdtg_set_phadadj(mode);
	}

	switch(mode) {
		case 480:
		case 640:
			/* Set Lcd Resolution (VGA) */
			corgi_ssp_lcdtg_send(RESCTL_ADRS, RESCTL_VGA);
			break;
		case 240:
		case 320:
		default:
			/* Set Lcd Resolution (QVGA) */
			corgi_ssp_lcdtg_send(RESCTL_ADRS, RESCTL_QVGA);
			break;
	}
}