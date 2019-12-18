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
struct rx8025_data {int ctrl1; int /*<<< orphan*/  client; } ;
struct i2c_client {scalar_t__ irq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int RX8025_BIT_CTRL1_CT ; 
 int RX8025_BIT_CTRL1_CT_1HZ ; 
 int /*<<< orphan*/  RX8025_REG_CTRL1 ; 
 struct rx8025_data* i2c_get_clientdata (struct i2c_client*) ; 
 int rx8025_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int rx8025_irq_set_state(struct device *dev, int enabled)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct rx8025_data *rx8025 = i2c_get_clientdata(client);
	int ctrl1;
	int err;

	if (client->irq <= 0)
		return -ENXIO;

	ctrl1 = rx8025->ctrl1 & ~RX8025_BIT_CTRL1_CT;
	if (enabled)
		ctrl1 |= RX8025_BIT_CTRL1_CT_1HZ;
	if (ctrl1 != rx8025->ctrl1) {
		rx8025->ctrl1 = ctrl1;
		err = rx8025_write_reg(rx8025->client, RX8025_REG_CTRL1,
				       rx8025->ctrl1);
		if (err)
			return err;
	}

	return 0;
}