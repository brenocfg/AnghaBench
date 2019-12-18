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
typedef  int /*<<< orphan*/  wr ;
struct tea5764_write_regs {int intreg; void* rdsbbl; void* rdsctrl; void* testreg; void* tnctrl; void* frqset; } ;
struct tea5764_regs {int intreg; int /*<<< orphan*/  rdsbbl; int /*<<< orphan*/  rdsctrl; int /*<<< orphan*/  testreg; int /*<<< orphan*/  tnctrl; int /*<<< orphan*/  frqset; } ;
struct tea5764_device {TYPE_1__* i2c_client; struct tea5764_regs regs; } ;
struct i2c_msg {int member_2; void* member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EIO ; 
 void* __cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

int tea5764_i2c_write(struct tea5764_device *radio)
{
	struct tea5764_write_regs wr;
	struct tea5764_regs *r = &radio->regs;
	struct i2c_msg msgs[1] = {
		{ radio->i2c_client->addr, 0, sizeof(wr), (void *) &wr },
	};
	wr.intreg  = r->intreg & 0xff;
	wr.frqset  = __cpu_to_be16(r->frqset);
	wr.tnctrl  = __cpu_to_be16(r->tnctrl);
	wr.testreg = __cpu_to_be16(r->testreg);
	wr.rdsctrl = __cpu_to_be16(r->rdsctrl);
	wr.rdsbbl  = __cpu_to_be16(r->rdsbbl);
	if (i2c_transfer(radio->i2c_client->adapter, msgs, 1) != 1)
		return -EIO;
	return 0;
}