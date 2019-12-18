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
struct mpc_i2c {int dummy; } ;

/* Variables and functions */
 int CCR_MEN ; 
 int CCR_MSTA ; 
 int CCR_MTX ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeccr (struct mpc_i2c*,int) ; 

__attribute__((used)) static void mpc_i2c_fixup(struct mpc_i2c *i2c)
{
	writeccr(i2c, 0);
	udelay(30);
	writeccr(i2c, CCR_MEN);
	udelay(30);
	writeccr(i2c, CCR_MSTA | CCR_MTX);
	udelay(30);
	writeccr(i2c, CCR_MSTA | CCR_MTX | CCR_MEN);
	udelay(30);
	writeccr(i2c, CCR_MEN);
	udelay(30);
}