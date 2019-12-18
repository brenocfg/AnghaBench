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
typedef  int uint32_t ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int I2C_BUSY ; 
 int I2C_ERR ; 
 int /*<<< orphan*/  MC2_UPLD_IIC ; 
 int /*<<< orphan*/  MC_ENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MC_TEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_I2CCTRL ; 
 int /*<<< orphan*/  P_MC2 ; 
 int RR7146 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR7146 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t I2Chandshake(struct comedi_device *dev, uint32_t val)
{
	/*  Write I2C command to I2C Transfer Control shadow register. */
	WR7146(P_I2CCTRL, val);

	/*  Upload I2C shadow registers into working registers and wait for */
	/*  upload confirmation. */

	MC_ENABLE(P_MC2, MC2_UPLD_IIC);
	while (!MC_TEST(P_MC2, MC2_UPLD_IIC)) ;

	/*  Wait until I2C bus transfer is finished or an error occurs. */
	while ((RR7146(P_I2CCTRL) & (I2C_BUSY | I2C_ERR)) == I2C_BUSY) ;

	/*  Return non-zero if I2C error occured. */
	return RR7146(P_I2CCTRL) & I2C_ERR;

}