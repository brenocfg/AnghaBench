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
struct max2165_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_PLL_CFG ; 
 int /*<<< orphan*/  max2165_mask_write_reg (struct max2165_priv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int max2165_set_osc(struct max2165_priv *priv, u8 osc /*MHz*/)
{
	u8 v;

	v = (osc / 2);
	if (v == 2)
		v = 0x7;
	else
		v -= 8;

	max2165_mask_write_reg(priv, REG_PLL_CFG, 0x07, v);

	return 0;
}