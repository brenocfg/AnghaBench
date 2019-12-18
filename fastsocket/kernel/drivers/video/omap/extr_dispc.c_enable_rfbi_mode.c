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

/* Variables and functions */
 int /*<<< orphan*/  DISPC_CONTROL ; 
 int /*<<< orphan*/  OMAP2_IO_ADDRESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFBI_CONTROL ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int dispc_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enable_rfbi_mode(int enable)
{
	u32 l;

	l = dispc_read_reg(DISPC_CONTROL);
	/* Enable RFBI, GPIO0/1 */
	l &= ~((1 << 11) | (1 << 15) | (1 << 16));
	l |= enable ? (1 << 11) : 0;
	/* RFBI En: GPIO0/1=10  RFBI Dis: GPIO0/1=11 */
	l |= 1 << 15;
	l |= enable ? 0 : (1 << 16);
	dispc_write_reg(DISPC_CONTROL, l);

	/* Set bypass mode in RFBI module */
	l = __raw_readl(OMAP2_IO_ADDRESS(RFBI_CONTROL));
	l |= enable ? 0 : (1 << 1);
	__raw_writel(l, OMAP2_IO_ADDRESS(RFBI_CONTROL));
}