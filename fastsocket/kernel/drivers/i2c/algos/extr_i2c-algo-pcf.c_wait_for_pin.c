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
struct i2c_algo_pcf_data {int /*<<< orphan*/  data; int /*<<< orphan*/  (* waitforpin ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int DEF_TIMEOUT ; 
 int EINTR ; 
 int ETIMEDOUT ; 
 int I2C_PCF_LAB ; 
 int I2C_PCF_PIN ; 
 int get_pcf (struct i2c_algo_pcf_data*,int) ; 
 int /*<<< orphan*/  handle_lab (struct i2c_algo_pcf_data*,int*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_for_pin(struct i2c_algo_pcf_data *adap, int *status)
{

	int timeout = DEF_TIMEOUT;

	*status = get_pcf(adap, 1);

	while ((*status & I2C_PCF_PIN) && --timeout) {
		adap->waitforpin(adap->data);
		*status = get_pcf(adap, 1);
	}
	if (*status & I2C_PCF_LAB) {
		handle_lab(adap, status);
		return -EINTR;
	}

	if (timeout == 0)
		return -ETIMEDOUT;

	return 0;
}