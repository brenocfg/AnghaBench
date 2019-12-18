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
struct i2c_pnx_algo_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_REG_STS (struct i2c_pnx_algo_data*) ; 
 int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int mstatus_active ; 

__attribute__((used)) static inline int wait_timeout(long timeout, struct i2c_pnx_algo_data *data)
{
	while (timeout > 0 &&
			(ioread32(I2C_REG_STS(data)) & mstatus_active)) {
		mdelay(1);
		timeout--;
	}
	return (timeout <= 0);
}