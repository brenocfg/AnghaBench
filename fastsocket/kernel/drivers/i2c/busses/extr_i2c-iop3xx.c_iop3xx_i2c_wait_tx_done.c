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
struct i2c_algo_iop3xx_data {int dummy; } ;

/* Variables and functions */
 int IOP3XX_ISR_ALD ; 
 int IOP3XX_ISR_BERRD ; 
 int IOP3XX_ISR_TXEMPTY ; 
 int /*<<< orphan*/  any_bits_set ; 
 int iop3xx_i2c_wait_event (struct i2c_algo_iop3xx_data*,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
iop3xx_i2c_wait_tx_done(struct i2c_algo_iop3xx_data *iop3xx_adap, int *status)
{
	return iop3xx_i2c_wait_event( 
		iop3xx_adap, 
	        IOP3XX_ISR_TXEMPTY | IOP3XX_ISR_ALD | IOP3XX_ISR_BERRD,
		status, any_bits_set);
}