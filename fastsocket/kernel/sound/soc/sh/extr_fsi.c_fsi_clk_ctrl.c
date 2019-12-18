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
typedef  int u32 ;
struct fsi_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_RST ; 
 scalar_t__ fsi_is_port_a (struct fsi_priv*) ; 
 int /*<<< orphan*/  fsi_master_mask_set (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void fsi_clk_ctrl(struct fsi_priv *fsi, int enable)
{
	u32 val = fsi_is_port_a(fsi) ? (1 << 0) : (1 << 4);

	if (enable)
		fsi_master_mask_set(CLK_RST, val, val);
	else
		fsi_master_mask_set(CLK_RST, val, 0);
}