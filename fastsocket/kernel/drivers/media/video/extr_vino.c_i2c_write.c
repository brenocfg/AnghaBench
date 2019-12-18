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
struct i2c_algo_sgi_data {int /*<<< orphan*/  data; int /*<<< orphan*/  (* wdata ) (int /*<<< orphan*/ ,unsigned char) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned char) ; 
 scalar_t__ wait_ack (struct i2c_algo_sgi_data*) ; 

__attribute__((used)) static int i2c_write(struct i2c_algo_sgi_data *adap, unsigned char *buf,
		     unsigned int len)
{
	int i;

	/* We are already in write state */
	for (i = 0; i < len; i++) {
		adap->wdata(adap->data, buf[i]);
		if (wait_ack(adap))
			return -EIO;
	}
	return 0;
}