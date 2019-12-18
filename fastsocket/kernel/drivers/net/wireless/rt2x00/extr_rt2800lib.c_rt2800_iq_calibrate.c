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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_IQ_GAIN_CAL_TX0_2G ; 
 int /*<<< orphan*/  EEPROM_IQ_GAIN_CAL_TX0_CH100_TO_CH138_5G ; 
 int /*<<< orphan*/  EEPROM_IQ_GAIN_CAL_TX0_CH140_TO_CH165_5G ; 
 int /*<<< orphan*/  EEPROM_IQ_GAIN_CAL_TX0_CH36_TO_CH64_5G ; 
 int /*<<< orphan*/  EEPROM_IQ_GAIN_CAL_TX1_2G ; 
 int /*<<< orphan*/  EEPROM_IQ_GAIN_CAL_TX1_CH100_TO_CH138_5G ; 
 int /*<<< orphan*/  EEPROM_IQ_GAIN_CAL_TX1_CH140_TO_CH165_5G ; 
 int /*<<< orphan*/  EEPROM_IQ_GAIN_CAL_TX1_CH36_TO_CH64_5G ; 
 int /*<<< orphan*/  EEPROM_IQ_PHASE_CAL_TX0_2G ; 
 int /*<<< orphan*/  EEPROM_IQ_PHASE_CAL_TX0_CH100_TO_CH138_5G ; 
 int /*<<< orphan*/  EEPROM_IQ_PHASE_CAL_TX0_CH140_TO_CH165_5G ; 
 int /*<<< orphan*/  EEPROM_IQ_PHASE_CAL_TX0_CH36_TO_CH64_5G ; 
 int /*<<< orphan*/  EEPROM_IQ_PHASE_CAL_TX1_2G ; 
 int /*<<< orphan*/  EEPROM_IQ_PHASE_CAL_TX1_CH100_TO_CH138_5G ; 
 int /*<<< orphan*/  EEPROM_IQ_PHASE_CAL_TX1_CH140_TO_CH165_5G ; 
 int /*<<< orphan*/  EEPROM_IQ_PHASE_CAL_TX1_CH36_TO_CH64_5G ; 
 int /*<<< orphan*/  EEPROM_RF_IQ_COMPENSATION_CONTROL ; 
 int /*<<< orphan*/  EEPROM_RF_IQ_IMBALANCE_COMPENSATION_CONTROL ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 
 int rt2x00_eeprom_byte (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2800_iq_calibrate(struct rt2x00_dev *rt2x00dev, int channel)
{
	u8 cal;

	/* TX0 IQ Gain */
	rt2800_bbp_write(rt2x00dev, 158, 0x2c);
	if (channel <= 14)
		cal = rt2x00_eeprom_byte(rt2x00dev, EEPROM_IQ_GAIN_CAL_TX0_2G);
	else if (channel >= 36 && channel <= 64)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_GAIN_CAL_TX0_CH36_TO_CH64_5G);
	else if (channel >= 100 && channel <= 138)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_GAIN_CAL_TX0_CH100_TO_CH138_5G);
	else if (channel >= 140 && channel <= 165)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_GAIN_CAL_TX0_CH140_TO_CH165_5G);
	else
		cal = 0;
	rt2800_bbp_write(rt2x00dev, 159, cal);

	/* TX0 IQ Phase */
	rt2800_bbp_write(rt2x00dev, 158, 0x2d);
	if (channel <= 14)
		cal = rt2x00_eeprom_byte(rt2x00dev, EEPROM_IQ_PHASE_CAL_TX0_2G);
	else if (channel >= 36 && channel <= 64)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_PHASE_CAL_TX0_CH36_TO_CH64_5G);
	else if (channel >= 100 && channel <= 138)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_PHASE_CAL_TX0_CH100_TO_CH138_5G);
	else if (channel >= 140 && channel <= 165)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_PHASE_CAL_TX0_CH140_TO_CH165_5G);
	else
		cal = 0;
	rt2800_bbp_write(rt2x00dev, 159, cal);

	/* TX1 IQ Gain */
	rt2800_bbp_write(rt2x00dev, 158, 0x4a);
	if (channel <= 14)
		cal = rt2x00_eeprom_byte(rt2x00dev, EEPROM_IQ_GAIN_CAL_TX1_2G);
	else if (channel >= 36 && channel <= 64)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_GAIN_CAL_TX1_CH36_TO_CH64_5G);
	else if (channel >= 100 && channel <= 138)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_GAIN_CAL_TX1_CH100_TO_CH138_5G);
	else if (channel >= 140 && channel <= 165)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_GAIN_CAL_TX1_CH140_TO_CH165_5G);
	else
		cal = 0;
	rt2800_bbp_write(rt2x00dev, 159, cal);

	/* TX1 IQ Phase */
	rt2800_bbp_write(rt2x00dev, 158, 0x4b);
	if (channel <= 14)
		cal = rt2x00_eeprom_byte(rt2x00dev, EEPROM_IQ_PHASE_CAL_TX1_2G);
	else if (channel >= 36 && channel <= 64)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_PHASE_CAL_TX1_CH36_TO_CH64_5G);
	else if (channel >= 100 && channel <= 138)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_PHASE_CAL_TX1_CH100_TO_CH138_5G);
	else if (channel >= 140 && channel <= 165)
		cal = rt2x00_eeprom_byte(rt2x00dev,
					 EEPROM_IQ_PHASE_CAL_TX1_CH140_TO_CH165_5G);
	else
		cal = 0;
	rt2800_bbp_write(rt2x00dev, 159, cal);

	/* FIXME: possible RX0, RX1 callibration ? */

	/* RF IQ compensation control */
	rt2800_bbp_write(rt2x00dev, 158, 0x04);
	cal = rt2x00_eeprom_byte(rt2x00dev, EEPROM_RF_IQ_COMPENSATION_CONTROL);
	rt2800_bbp_write(rt2x00dev, 159, cal != 0xff ? cal : 0);

	/* RF IQ imbalance compensation control */
	rt2800_bbp_write(rt2x00dev, 158, 0x03);
	cal = rt2x00_eeprom_byte(rt2x00dev,
				 EEPROM_RF_IQ_IMBALANCE_COMPENSATION_CONTROL);
	rt2800_bbp_write(rt2x00dev, 159, cal != 0xff ? cal : 0);
}