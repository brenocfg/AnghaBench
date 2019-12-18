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
struct w9968cf_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  W9968CF_I2C_BUS_DELAY ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int w9968cf_read_reg (struct w9968cf_device*,int) ; 

__attribute__((used)) static int w9968cf_read_sb(struct w9968cf_device* cam)
{
	int v = 0;

	v = w9968cf_read_reg(cam, 0x01);
	udelay(W9968CF_I2C_BUS_DELAY);

	return v;
}