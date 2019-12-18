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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LCNTAB16 (int,int) ; 
 int /*<<< orphan*/  b43_lcntab_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void b43_phy_lcn_set_bbmult(struct b43_wldev *dev, u8 m0)
{
	b43_lcntab_write(dev, B43_LCNTAB16(0x00, 0x57), m0 << 8);
}