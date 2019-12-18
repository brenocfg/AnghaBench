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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 int CMD_EEprom_Close ; 
 int CMD_EEprom_Open ; 
 int /*<<< orphan*/  R01_TIMING_CONTROL_LOW ; 
 int /*<<< orphan*/  R03_TABLE_ADDR ; 
 int /*<<< orphan*/  R04_WTRAM_DATA_L ; 
 int /*<<< orphan*/  R05_WTRAM_DATA_M ; 
 int /*<<< orphan*/  R06_WTRAM_DATA_H ; 
 int /*<<< orphan*/  R07_TABLE_LEN ; 
 int /*<<< orphan*/  R08_RAM_WRITE_ACTION ; 
 int** eeprom_data ; 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tv_8532WriteEEprom(struct gspca_dev *gspca_dev)
{
	int i;

	reg_w1(gspca_dev, R01_TIMING_CONTROL_LOW, CMD_EEprom_Open);
	for (i = 0; i < ARRAY_SIZE(eeprom_data); i++) {
		reg_w1(gspca_dev, R03_TABLE_ADDR, i);
		reg_w1(gspca_dev, R04_WTRAM_DATA_L, eeprom_data[i][2]);
		reg_w1(gspca_dev, R05_WTRAM_DATA_M, eeprom_data[i][1]);
		reg_w1(gspca_dev, R06_WTRAM_DATA_H, eeprom_data[i][0]);
		reg_w1(gspca_dev, R08_RAM_WRITE_ACTION, 0);
	}
	reg_w1(gspca_dev, R07_TABLE_LEN, i);
	reg_w1(gspca_dev, R01_TIMING_CONTROL_LOW, CMD_EEprom_Close);
}