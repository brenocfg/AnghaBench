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
typedef  scalar_t__ u32 ;
struct max2165_priv {int bb_filter_8mhz_cfg; int bb_filter_7mhz_cfg; } ;

/* Variables and functions */
 scalar_t__ BANDWIDTH_8_MHZ ; 
 int /*<<< orphan*/  REG_BASEBAND_CTRL ; 
 int /*<<< orphan*/  max2165_mask_write_reg (struct max2165_priv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int max2165_set_bandwidth(struct max2165_priv *priv, u32 bw)
{
	u8 val;

	if (bw == BANDWIDTH_8_MHZ)
		val = priv->bb_filter_8mhz_cfg;
	else
		val = priv->bb_filter_7mhz_cfg;

	max2165_mask_write_reg(priv, REG_BASEBAND_CTRL, 0xF0, val << 4);

	return 0;
}