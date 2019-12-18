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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LCNTAB32 (int,int) ; 
 int /*<<< orphan*/  b43_lcntab_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_lcntab_write (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_phy_lcn_rewrite_rfpower_table(struct b43_wldev *dev)
{
	int i;
	u32 tmp;
	for (i = 0; i < 128; i++) {
		tmp = b43_lcntab_read(dev, B43_LCNTAB32(0x7, 0x240 + i));
		b43_lcntab_write(dev, B43_LCNTAB32(0x7, 0x240 + i), tmp);
	}
}