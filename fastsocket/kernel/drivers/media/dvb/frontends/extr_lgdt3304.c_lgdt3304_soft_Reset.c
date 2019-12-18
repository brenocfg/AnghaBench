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
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lgdt3304_i2c_write_reg (struct dvb_frontend*,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int lgdt3304_soft_Reset(struct dvb_frontend *fe)
{
	lgdt3304_i2c_write_reg(fe, 0x0002, 0x9a);
	lgdt3304_i2c_write_reg(fe, 0x0002, 0x9b);
	mdelay(200);
	return 0;
}