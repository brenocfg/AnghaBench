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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_IO (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPW_INDIRECT_ADDR ; 
 int IPW_INDIRECT_ADDR_MASK ; 
 int IPW_INDIRECT_DATA ; 
 int /*<<< orphan*/  _ipw_write32 (struct ipw_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  _ipw_write8 (struct ipw_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _ipw_write_reg8(struct ipw_priv *priv, u32 reg, u8 value)
{
	u32 aligned_addr = reg & IPW_INDIRECT_ADDR_MASK;	/* dword align */
	u32 dif_len = reg - aligned_addr;

	IPW_DEBUG_IO(" reg = 0x%8X : value = 0x%8X\n", reg, value);
	_ipw_write32(priv, IPW_INDIRECT_ADDR, aligned_addr);
	_ipw_write8(priv, IPW_INDIRECT_DATA + dif_len, value);
}