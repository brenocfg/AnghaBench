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

/* Variables and functions */
 int /*<<< orphan*/  lcdtg_i2c_send_byte (int,int) ; 
 int /*<<< orphan*/  lcdtg_i2c_send_start (int) ; 
 int /*<<< orphan*/  lcdtg_i2c_send_stop (int) ; 
 int /*<<< orphan*/  lcdtg_i2c_wait_ack (int) ; 

__attribute__((used)) static void lcdtg_set_common_voltage(u8 base_data, u8 data)
{
	/* Set Common Voltage to M62332FP via I2C */
	lcdtg_i2c_send_start(base_data);
	lcdtg_i2c_send_byte(base_data, 0x9c);
	lcdtg_i2c_wait_ack(base_data);
	lcdtg_i2c_send_byte(base_data, 0x00);
	lcdtg_i2c_wait_ack(base_data);
	lcdtg_i2c_send_byte(base_data, data);
	lcdtg_i2c_wait_ack(base_data);
	lcdtg_i2c_send_stop(base_data);
}