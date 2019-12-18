#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
struct TYPE_2__ {int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;
struct rtc_wkalrm {scalar_t__ enabled; TYPE_1__ time; int /*<<< orphan*/  pending; } ;
struct i2c_client {int dummy; } ;
struct ds1307 {unsigned char* regs; int (* read_block_data ) (struct i2c_client*,int /*<<< orphan*/ ,int,unsigned char*) ;int (* write_block_data ) (struct i2c_client*,int /*<<< orphan*/ ,int,unsigned char*) ;int /*<<< orphan*/  flags; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned char DS1337_BIT_A1I ; 
 unsigned char DS1337_BIT_A1IE ; 
 unsigned char DS1337_BIT_A2I ; 
 unsigned char DS1337_BIT_A2IE ; 
 int /*<<< orphan*/  DS1339_REG_ALARM1_SECS ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  HAS_ALARM ; 
 unsigned char bin2bcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct ds1307* i2c_get_clientdata (struct i2c_client*) ; 
 int stub1 (struct i2c_client*,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int stub2 (struct i2c_client*,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int ds1337_set_alarm(struct device *dev, struct rtc_wkalrm *t)
{
	struct i2c_client       *client = to_i2c_client(dev);
	struct ds1307		*ds1307 = i2c_get_clientdata(client);
	unsigned char		*buf = ds1307->regs;
	u8			control, status;
	int			ret;

	if (!test_bit(HAS_ALARM, &ds1307->flags))
		return -EINVAL;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, enabled=%d, pending=%d\n",
		"alarm set", t->time.tm_sec, t->time.tm_min,
		t->time.tm_hour, t->time.tm_mday,
		t->enabled, t->pending);

	/* read current status of both alarms and the chip */
	ret = ds1307->read_block_data(client,
			DS1339_REG_ALARM1_SECS, 9, buf);
	if (ret != 9) {
		dev_err(dev, "%s error %d\n", "alarm write", ret);
		return -EIO;
	}
	control = ds1307->regs[7];
	status = ds1307->regs[8];

	dev_dbg(dev, "%s: %02x %02x %02x %02x, %02x %02x %02x, %02x %02x\n",
			"alarm set (old status)",
			ds1307->regs[0], ds1307->regs[1],
			ds1307->regs[2], ds1307->regs[3],
			ds1307->regs[4], ds1307->regs[5],
			ds1307->regs[6], control, status);

	/* set ALARM1, using 24 hour and day-of-month modes */
	buf[0] = bin2bcd(t->time.tm_sec);
	buf[1] = bin2bcd(t->time.tm_min);
	buf[2] = bin2bcd(t->time.tm_hour);
	buf[3] = bin2bcd(t->time.tm_mday);

	/* set ALARM2 to non-garbage */
	buf[4] = 0;
	buf[5] = 0;
	buf[6] = 0;

	/* optionally enable ALARM1 */
	buf[7] = control & ~(DS1337_BIT_A1IE | DS1337_BIT_A2IE);
	if (t->enabled) {
		dev_dbg(dev, "alarm IRQ armed\n");
		buf[7] |= DS1337_BIT_A1IE;	/* only ALARM1 is used */
	}
	buf[8] = status & ~(DS1337_BIT_A1I | DS1337_BIT_A2I);

	ret = ds1307->write_block_data(client,
			DS1339_REG_ALARM1_SECS, 9, buf);
	if (ret < 0) {
		dev_err(dev, "can't set alarm time\n");
		return ret;
	}

	return 0;
}