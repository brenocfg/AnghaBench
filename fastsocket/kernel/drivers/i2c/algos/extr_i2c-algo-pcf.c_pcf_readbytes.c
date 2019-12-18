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
struct i2c_algo_pcf_data {int dummy; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; struct i2c_algo_pcf_data* algo_data; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  I2C_PCF_ESO ; 
 int I2C_PCF_LRB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 char i2c_inb (struct i2c_algo_pcf_data*) ; 
 int /*<<< orphan*/  i2c_repstart (struct i2c_algo_pcf_data*) ; 
 int /*<<< orphan*/  i2c_stop (struct i2c_algo_pcf_data*) ; 
 int /*<<< orphan*/  set_pcf (struct i2c_algo_pcf_data*,int,int /*<<< orphan*/ ) ; 
 int wait_for_pin (struct i2c_algo_pcf_data*,int*) ; 

__attribute__((used)) static int pcf_readbytes(struct i2c_adapter *i2c_adap, char *buf,
			 int count, int last)
{
	int i, status;
	struct i2c_algo_pcf_data *adap = i2c_adap->algo_data;
	int wfp;

	/* increment number of bytes to read by one -- read dummy byte */
	for (i = 0; i <= count; i++) {

		if ((wfp = wait_for_pin(adap, &status))) {
			if (wfp == -EINTR)
				return -EINTR; /* arbitration lost */

			i2c_stop(adap);
			dev_err(&i2c_adap->dev, "pcf_readbytes timed out.\n");
			return -1;
		}

		if ((status & I2C_PCF_LRB) && (i != count)) {
			i2c_stop(adap);
			dev_err(&i2c_adap->dev, "i2c_read: i2c_inb, No ack.\n");
			return -1;
		}

		if (i == count - 1) {
			set_pcf(adap, 1, I2C_PCF_ESO);
		} else if (i == count) {
			if (last)
				i2c_stop(adap);
			else
				i2c_repstart(adap);
		}

		if (i)
			buf[i - 1] = i2c_inb(adap);
		else
			i2c_inb(adap); /* dummy read */
	}

	return i - 1;
}