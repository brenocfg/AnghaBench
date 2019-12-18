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
typedef  int u32 ;
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_IO (char*,int) ; 
 int /*<<< orphan*/  IPW_INDIRECT_ADDR ; 
 int IPW_INDIRECT_ADDR_MASK ; 
 int /*<<< orphan*/  IPW_INDIRECT_DATA ; 
 int _ipw_read32 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ipw_write32 (struct ipw_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u8 _ipw_read_reg8(struct ipw_priv *priv, u32 reg)
{
	u32 word;
	_ipw_write32(priv, IPW_INDIRECT_ADDR, reg & IPW_INDIRECT_ADDR_MASK);
	IPW_DEBUG_IO(" reg = 0x%8X :\n", reg);
	word = _ipw_read32(priv, IPW_INDIRECT_DATA);
	return (word >> ((reg & 0x3) * 8)) & 0xff;
}