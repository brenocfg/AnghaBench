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
struct max2165_priv {int tf_ntch_low_cfg; int tf_ntch_hi_cfg; int tf_balun_low_ref; int tf_balun_hi_ref; int bb_filter_7mhz_cfg; int bb_filter_8mhz_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ROM_TABLE_ADDR ; 
 int /*<<< orphan*/  REG_ROM_TABLE_DATA ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  max2165_read_reg (struct max2165_priv*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  max2165_write_reg (struct max2165_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max2165_read_rom_table(struct max2165_priv *priv)
{
	u8 dat[3];
	int i;

	for (i = 0; i < 3; i++) {
		max2165_write_reg(priv, REG_ROM_TABLE_ADDR, i + 1);
		max2165_read_reg(priv, REG_ROM_TABLE_DATA, &dat[i]);
	}

	priv->tf_ntch_low_cfg = dat[0] >> 4;
	priv->tf_ntch_hi_cfg = dat[0] & 0x0F;
	priv->tf_balun_low_ref = dat[1] & 0x0F;
	priv->tf_balun_hi_ref = dat[1] >> 4;
	priv->bb_filter_7mhz_cfg = dat[2] & 0x0F;
	priv->bb_filter_8mhz_cfg = dat[2] >> 4;

	dprintk("tf_ntch_low_cfg = 0x%X\n", priv->tf_ntch_low_cfg);
	dprintk("tf_ntch_hi_cfg = 0x%X\n", priv->tf_ntch_hi_cfg);
	dprintk("tf_balun_low_ref = 0x%X\n", priv->tf_balun_low_ref);
	dprintk("tf_balun_hi_ref = 0x%X\n", priv->tf_balun_hi_ref);
	dprintk("bb_filter_7mhz_cfg = 0x%X\n", priv->bb_filter_7mhz_cfg);
	dprintk("bb_filter_8mhz_cfg = 0x%X\n", priv->bb_filter_8mhz_cfg);

	return 0;
}