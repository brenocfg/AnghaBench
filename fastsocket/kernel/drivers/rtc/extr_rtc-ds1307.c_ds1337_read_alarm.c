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
struct TYPE_2__ {int tm_mon; int tm_year; int tm_wday; int tm_yday; int tm_isdst; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct rtc_wkalrm {int enabled; int pending; TYPE_1__ time; } ;
struct i2c_client {int dummy; } ;
struct ds1307 {int (* read_block_data ) (struct i2c_client*,int /*<<< orphan*/ ,int,int*) ;int* regs; int /*<<< orphan*/  flags; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DS1337_BIT_A1I ; 
 int DS1337_BIT_A1IE ; 
 int /*<<< orphan*/  DS1339_REG_ALARM1_SECS ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  HAS_ALARM ; 
 void* bcd2bin (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,int,int,int,int,int,int,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,int) ; 
 struct ds1307* i2c_get_clientdata (struct i2c_client*) ; 
 int stub1 (struct i2c_client*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int ds1337_read_alarm(struct device *dev, struct rtc_wkalrm *t)
{
	struct i2c_client       *client = to_i2c_client(dev);
	struct ds1307		*ds1307 = i2c_get_clientdata(client);
	int			ret;

	if (!test_bit(HAS_ALARM, &ds1307->flags))
		return -EINVAL;

	/* read all ALARM1, ALARM2, and status registers at once */
	ret = ds1307->read_block_data(client,
			DS1339_REG_ALARM1_SECS, 9, ds1307->regs);
	if (ret != 9) {
		dev_err(dev, "%s error %d\n", "alarm read", ret);
		return -EIO;
	}

	dev_dbg(dev, "%s: %02x %02x %02x %02x, %02x %02x %02x, %02x %02x\n",
			"alarm read",
			ds1307->regs[0], ds1307->regs[1],
			ds1307->regs[2], ds1307->regs[3],
			ds1307->regs[4], ds1307->regs[5],
			ds1307->regs[6], ds1307->regs[7],
			ds1307->regs[8]);

	/* report alarm time (ALARM1); assume 24 hour and day-of-month modes,
	 * and that all four fields are checked matches
	 */
	t->time.tm_sec = bcd2bin(ds1307->regs[0] & 0x7f);
	t->time.tm_min = bcd2bin(ds1307->regs[1] & 0x7f);
	t->time.tm_hour = bcd2bin(ds1307->regs[2] & 0x3f);
	t->time.tm_mday = bcd2bin(ds1307->regs[3] & 0x3f);
	t->time.tm_mon = -1;
	t->time.tm_year = -1;
	t->time.tm_wday = -1;
	t->time.tm_yday = -1;
	t->time.tm_isdst = -1;

	/* ... and status */
	t->enabled = !!(ds1307->regs[7] & DS1337_BIT_A1IE);
	t->pending = !!(ds1307->regs[8] & DS1337_BIT_A1I);

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, enabled=%d, pending=%d\n",
		"alarm read", t->time.tm_sec, t->time.tm_min,
		t->time.tm_hour, t->time.tm_mday,
		t->enabled, t->pending);

	return 0;
}