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
typedef  int u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LM93_REG_CONFIG ; 
 int /*<<< orphan*/  LM93_REG_GPI_VID_CTL ; 
 int /*<<< orphan*/  LM93_REG_MISC_ERR_MASK ; 
 int /*<<< orphan*/  LM93_REG_SLEEP_CONTROL ; 
 int /*<<< orphan*/  LM93_REG_STATUS_CONTROL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ init ; 
 int lm93_read_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm93_write_byte (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__* vccp_limit_type ; 
 scalar_t__ vid_agtl ; 

__attribute__((used)) static void lm93_init_client(struct i2c_client *client)
{
	int i;
	u8 reg;

	/* configure VID pin input thresholds */
	reg = lm93_read_byte(client, LM93_REG_GPI_VID_CTL);
	lm93_write_byte(client, LM93_REG_GPI_VID_CTL,
			reg | (vid_agtl ? 0x03 : 0x00));

	if (init) {
		/* enable #ALERT pin */
		reg = lm93_read_byte(client, LM93_REG_CONFIG);
		lm93_write_byte(client, LM93_REG_CONFIG, reg | 0x08);

		/* enable ASF mode for BMC status registers */
		reg = lm93_read_byte(client, LM93_REG_STATUS_CONTROL);
		lm93_write_byte(client, LM93_REG_STATUS_CONTROL, reg | 0x02);

		/* set sleep state to S0 */
		lm93_write_byte(client, LM93_REG_SLEEP_CONTROL, 0);

		/* unmask #VRDHOT and dynamic VCCP (if nec) error events */
		reg = lm93_read_byte(client, LM93_REG_MISC_ERR_MASK);
		reg &= ~0x03;
		reg &= ~(vccp_limit_type[0] ? 0x10 : 0);
		reg &= ~(vccp_limit_type[1] ? 0x20 : 0);
		lm93_write_byte(client, LM93_REG_MISC_ERR_MASK, reg);
	}

	/* start monitoring */
	reg = lm93_read_byte(client, LM93_REG_CONFIG);
	lm93_write_byte(client, LM93_REG_CONFIG, reg | 0x01);

	/* spin until ready */
	for (i=0; i<20; i++) {
		msleep(10);
		if ((lm93_read_byte(client, LM93_REG_CONFIG) & 0x80) == 0x80)
			return;
	}

	dev_warn(&client->dev,"timed out waiting for sensor "
		 "chip to signal ready!\n");
}