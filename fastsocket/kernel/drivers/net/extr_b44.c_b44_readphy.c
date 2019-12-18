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
typedef  int /*<<< orphan*/  u32 ;
struct b44 {scalar_t__ phy_addr; } ;

/* Variables and functions */
 scalar_t__ B44_PHY_ADDR_NO_PHY ; 
 int __b44_readphy (struct b44*,scalar_t__,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int b44_readphy(struct b44 *bp, int reg, u32 *val)
{
	if (bp->phy_addr == B44_PHY_ADDR_NO_PHY)
		return 0;

	return __b44_readphy(bp, bp->phy_addr, reg, val);
}