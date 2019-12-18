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
typedef  int /*<<< orphan*/  u16 ;
struct w9968cf_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  W9968CF_I2C_BUS_DELAY ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int w9968cf_write_reg (struct w9968cf_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int w9968cf_write_sb(struct w9968cf_device* cam, u16 value)
{
	int err = 0;

	err = w9968cf_write_reg(cam, value, 0x01);
	udelay(W9968CF_I2C_BUS_DELAY);

	return err;
}