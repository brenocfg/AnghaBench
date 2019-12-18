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
struct skge_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SK_GMAC_REG (int,int) ; 
 scalar_t__ skge_read16 (struct skge_hw const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 gma_read32(const struct skge_hw *hw, int port, int reg)
{
	return (u32) skge_read16(hw, SK_GMAC_REG(port,reg))
		| ((u32)skge_read16(hw, SK_GMAC_REG(port,reg+4)) << 16);
}