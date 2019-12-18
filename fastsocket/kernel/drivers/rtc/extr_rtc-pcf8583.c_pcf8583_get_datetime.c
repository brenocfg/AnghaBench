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
struct rtc_time {unsigned char tm_year; unsigned char tm_wday; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct i2c_msg {int len; unsigned char* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct i2c_client {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 void* bcd2bin (unsigned char) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pcf8583_get_datetime(struct i2c_client *client, struct rtc_time *dt)
{
	unsigned char buf[8], addr[1] = { 1 };
	struct i2c_msg msgs[2] = {
		{
			.addr = client->addr,
			.flags = 0,
			.len = 1,
			.buf = addr,
		}, {
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 6,
			.buf = buf,
		}
	};
	int ret;

	memset(buf, 0, sizeof(buf));

	ret = i2c_transfer(client->adapter, msgs, 2);
	if (ret == 2) {
		dt->tm_year = buf[4] >> 6;
		dt->tm_wday = buf[5] >> 5;

		buf[4] &= 0x3f;
		buf[5] &= 0x1f;

		dt->tm_sec = bcd2bin(buf[1]);
		dt->tm_min = bcd2bin(buf[2]);
		dt->tm_hour = bcd2bin(buf[3]);
		dt->tm_mday = bcd2bin(buf[4]);
		dt->tm_mon = bcd2bin(buf[5]) - 1;
	}

	return ret == 2 ? 0 : -EIO;
}