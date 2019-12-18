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
typedef  int u16 ;
struct lp3971 {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int /*<<< orphan*/  lp3971_i2c_read (int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 lp3971_reg_read(struct lp3971 *lp3971, u8 reg)
{
	u16 val = 0;

	mutex_lock(&lp3971->io_lock);

	lp3971_i2c_read(lp3971->i2c, reg, 1, &val);

	dev_dbg(lp3971->dev, "reg read 0x%02x -> 0x%02x\n", (int)reg,
		(unsigned)val&0xff);

	mutex_unlock(&lp3971->io_lock);

	return val & 0xff;
}