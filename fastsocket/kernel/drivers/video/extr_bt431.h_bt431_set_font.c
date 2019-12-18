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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct bt431_regs {int dummy; } ;

/* Variables and functions */
 int BT431_REG_CRAM_BASE ; 
 int BT431_REG_CRAM_END ; 
 int /*<<< orphan*/  bt431_select_reg (struct bt431_regs*,int) ; 
 int /*<<< orphan*/  bt431_write_cmap_inc (struct bt431_regs*,int) ; 

__attribute__((used)) static inline void bt431_set_font(struct bt431_regs *regs, u8 fgc,
				  u16 width, u16 height)
{
	int i;
	u16 fgp = fgc ? 0xffff : 0x0000;
	u16 bgp = fgc ? 0x0000 : 0xffff;

	bt431_select_reg(regs, BT431_REG_CRAM_BASE);
	for (i = BT431_REG_CRAM_BASE; i <= BT431_REG_CRAM_END; i++) {
		u16 value;

		if (height << 6 <= i << 3)
			value = bgp;
		else if (width <= i % 8 << 3)
			value = bgp;
		else if (((width >> 3) & 0xffff) > i % 8)
			value = fgp;
		else
			value = fgp & ~(bgp << (width % 8 << 1));

		bt431_write_cmap_inc(regs, value);
	}
}