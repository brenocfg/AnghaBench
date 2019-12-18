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
typedef  int u_int8_t ;
struct sh_mobile_i2c_data {int sr; int /*<<< orphan*/  dev; int /*<<< orphan*/  wait; } ;
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int HZ ; 
 int /*<<< orphan*/  ICSR (struct sh_mobile_i2c_data*) ; 
 int ICSR_AL ; 
 int ICSR_BUSY ; 
 int ICSR_TACK ; 
 int /*<<< orphan*/  OP_START ; 
 int SW_DONE ; 
 int /*<<< orphan*/  activate_ch (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  deactivate_ch (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct sh_mobile_i2c_data* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_op (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ioread8 (int /*<<< orphan*/ ) ; 
 int start_ch (struct sh_mobile_i2c_data*,struct i2c_msg*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sh_mobile_i2c_xfer(struct i2c_adapter *adapter,
			      struct i2c_msg *msgs,
			      int num)
{
	struct sh_mobile_i2c_data *pd = i2c_get_adapdata(adapter);
	struct i2c_msg	*msg;
	int err = 0;
	u_int8_t val;
	int i, k, retry_count;

	activate_ch(pd);

	/* Process all messages */
	for (i = 0; i < num; i++) {
		msg = &msgs[i];

		err = start_ch(pd, msg);
		if (err)
			break;

		i2c_op(pd, OP_START, 0);

		/* The interrupt handler takes care of the rest... */
		k = wait_event_timeout(pd->wait,
				       pd->sr & (ICSR_TACK | SW_DONE),
				       5 * HZ);
		if (!k)
			dev_err(pd->dev, "Transfer request timed out\n");

		retry_count = 1000;
again:
		val = ioread8(ICSR(pd));

		dev_dbg(pd->dev, "val 0x%02x pd->sr 0x%02x\n", val, pd->sr);

		/* the interrupt handler may wake us up before the
		 * transfer is finished, so poll the hardware
		 * until we're done.
		 */
		if (val & ICSR_BUSY) {
			udelay(10);
			if (retry_count--)
				goto again;

			err = -EIO;
			dev_err(pd->dev, "Polling timed out\n");
			break;
		}

		/* handle missing acknowledge and arbitration lost */
		if ((val | pd->sr) & (ICSR_TACK | ICSR_AL)) {
			err = -EIO;
			break;
		}
	}

	deactivate_ch(pd);

	if (!err)
		err = num;
	return err;
}