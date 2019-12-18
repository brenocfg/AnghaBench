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
typedef  int /*<<< orphan*/  v ;
typedef  int /*<<< orphan*/  u8 ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  demod_address; } ;
struct drx397xD_state {int /*<<< orphan*/  i2c; TYPE_1__ config; } ;
typedef  int /*<<< orphan*/  a ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _read16(struct drx397xD_state *s, __le32 i2c_adr)
{
	int rc;
	u8 a[4];
	__le16 v;
	struct i2c_msg msg[2] = {
		{
			.addr = s->config.demod_address,
			.flags = 0,
			.buf = a,
			.len = sizeof(a)
		}, {
			.addr = s->config.demod_address,
			.flags = I2C_M_RD,
			.buf = (u8 *)&v,
			.len = sizeof(v)
		}
	};

	*(__le32 *) a = i2c_adr;

	rc = i2c_transfer(s->i2c, msg, 2);
	if (rc != 2)
		return -EIO;

	return le16_to_cpu(v);
}