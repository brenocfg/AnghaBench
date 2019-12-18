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
struct i2c_msg {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; int /*<<< orphan*/  addr; } ;
struct i2c_algo_sgi_data {int dummy; } ;
struct i2c_adapter {struct i2c_algo_sgi_data* algo_data; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 int do_address (struct i2c_algo_sgi_data*,int /*<<< orphan*/ ,int) ; 
 int i2c_read (struct i2c_algo_sgi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_write (struct i2c_algo_sgi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sgi_xfer(struct i2c_adapter *i2c_adap, struct i2c_msg *msgs,
		    int num)
{
	struct i2c_algo_sgi_data *adap = i2c_adap->algo_data;
	struct i2c_msg *p;
	int i, err = 0;

	for (i = 0; !err && i < num; i++) {
		p = &msgs[i];
		err = do_address(adap, p->addr, p->flags & I2C_M_RD);
		if (err || !p->len)
			continue;
		if (p->flags & I2C_M_RD)
			err = i2c_read(adap, p->buf, p->len);
		else
			err = i2c_write(adap, p->buf, p->len);
	}

	return (err < 0) ? err : i;
}