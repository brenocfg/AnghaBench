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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_dev {int /*<<< orphan*/  csr_mutex; int /*<<< orphan*/ * eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_CTRL ; 
 int /*<<< orphan*/  EFUSE_CTRL_3290 ; 
 int /*<<< orphan*/  EFUSE_CTRL_ADDRESS_IN ; 
 int /*<<< orphan*/  EFUSE_CTRL_KICK ; 
 int /*<<< orphan*/  EFUSE_CTRL_MODE ; 
 int /*<<< orphan*/  EFUSE_DATA0 ; 
 int /*<<< orphan*/  EFUSE_DATA0_3290 ; 
 int /*<<< orphan*/  EFUSE_DATA1 ; 
 int /*<<< orphan*/  EFUSE_DATA1_3290 ; 
 int /*<<< orphan*/  EFUSE_DATA2 ; 
 int /*<<< orphan*/  EFUSE_DATA2_3290 ; 
 int /*<<< orphan*/  EFUSE_DATA3 ; 
 int /*<<< orphan*/  EFUSE_DATA3_3290 ; 
 int /*<<< orphan*/  RT3290 ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_regbusy_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_register_read_lock (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_register_write_lock (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2800_efuse_read(struct rt2x00_dev *rt2x00dev, unsigned int i)
{
	u32 reg;
	u16 efuse_ctrl_reg;
	u16 efuse_data0_reg;
	u16 efuse_data1_reg;
	u16 efuse_data2_reg;
	u16 efuse_data3_reg;

	if (rt2x00_rt(rt2x00dev, RT3290)) {
		efuse_ctrl_reg = EFUSE_CTRL_3290;
		efuse_data0_reg = EFUSE_DATA0_3290;
		efuse_data1_reg = EFUSE_DATA1_3290;
		efuse_data2_reg = EFUSE_DATA2_3290;
		efuse_data3_reg = EFUSE_DATA3_3290;
	} else {
		efuse_ctrl_reg = EFUSE_CTRL;
		efuse_data0_reg = EFUSE_DATA0;
		efuse_data1_reg = EFUSE_DATA1;
		efuse_data2_reg = EFUSE_DATA2;
		efuse_data3_reg = EFUSE_DATA3;
	}
	mutex_lock(&rt2x00dev->csr_mutex);

	rt2800_register_read_lock(rt2x00dev, efuse_ctrl_reg, &reg);
	rt2x00_set_field32(&reg, EFUSE_CTRL_ADDRESS_IN, i);
	rt2x00_set_field32(&reg, EFUSE_CTRL_MODE, 0);
	rt2x00_set_field32(&reg, EFUSE_CTRL_KICK, 1);
	rt2800_register_write_lock(rt2x00dev, efuse_ctrl_reg, reg);

	/* Wait until the EEPROM has been loaded */
	rt2800_regbusy_read(rt2x00dev, efuse_ctrl_reg, EFUSE_CTRL_KICK, &reg);
	/* Apparently the data is read from end to start */
	rt2800_register_read_lock(rt2x00dev, efuse_data3_reg, &reg);
	/* The returned value is in CPU order, but eeprom is le */
	*(u32 *)&rt2x00dev->eeprom[i] = cpu_to_le32(reg);
	rt2800_register_read_lock(rt2x00dev, efuse_data2_reg, &reg);
	*(u32 *)&rt2x00dev->eeprom[i + 2] = cpu_to_le32(reg);
	rt2800_register_read_lock(rt2x00dev, efuse_data1_reg, &reg);
	*(u32 *)&rt2x00dev->eeprom[i + 4] = cpu_to_le32(reg);
	rt2800_register_read_lock(rt2x00dev, efuse_data0_reg, &reg);
	*(u32 *)&rt2x00dev->eeprom[i + 6] = cpu_to_le32(reg);

	mutex_unlock(&rt2x00dev->csr_mutex);
}