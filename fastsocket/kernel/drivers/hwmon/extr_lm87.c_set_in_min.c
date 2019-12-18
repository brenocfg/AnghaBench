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
struct lm87_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * in_min; int /*<<< orphan*/ * in_scale; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IN_TO_REG (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LM87_REG_AIN_MIN (int) ; 
 int /*<<< orphan*/  LM87_REG_IN_MIN (int) ; 
 struct lm87_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  lm87_write_value (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static void set_in_min(struct device *dev, const char *buf, int nr)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct lm87_data *data = i2c_get_clientdata(client);
	long val = simple_strtol(buf, NULL, 10);

	mutex_lock(&data->update_lock);
	data->in_min[nr] = IN_TO_REG(val, data->in_scale[nr]);
	lm87_write_value(client, nr<6 ? LM87_REG_IN_MIN(nr) :
			 LM87_REG_AIN_MIN(nr-6), data->in_min[nr]);
	mutex_unlock(&data->update_lock);
}