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
struct cx18_i2c_algo_callback_data {int bus_index; struct cx18* cx; } ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_REG_I2C_1_RD ; 
 int /*<<< orphan*/  CX18_REG_I2C_2_RD ; 
 int GETSCL_BIT ; 
 int cx18_read_reg (struct cx18*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx18_getscl(void *data)
{
	struct cx18 *cx = ((struct cx18_i2c_algo_callback_data *)data)->cx;
	int bus_index = ((struct cx18_i2c_algo_callback_data *)data)->bus_index;
	u32 addr = bus_index ? CX18_REG_I2C_2_RD : CX18_REG_I2C_1_RD;

	return cx18_read_reg(cx, addr) & GETSCL_BIT;
}