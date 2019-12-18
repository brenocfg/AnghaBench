#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pmagbafb_par {int dummy; } ;
struct TYPE_2__ {unsigned int len; } ;
struct fb_info {TYPE_1__ cmap; struct pmagbafb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT459_ADDR_HI ; 
 int /*<<< orphan*/  BT459_ADDR_LO ; 
 int /*<<< orphan*/  BT459_CMAP ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dac_write (struct pmagbafb_par*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int pmagbafb_setcolreg(unsigned int regno, unsigned int red,
			      unsigned int green, unsigned int blue,
			      unsigned int transp, struct fb_info *info)
{
	struct pmagbafb_par *par = info->par;

	BUG_ON(regno >= info->cmap.len);

	red   >>= 8;	/* The cmap fields are 16 bits    */
	green >>= 8;	/* wide, but the hardware colormap */
	blue  >>= 8;	/* registers are only 8 bits wide */

	mb();
	dac_write(par, BT459_ADDR_LO, regno);
	dac_write(par, BT459_ADDR_HI, 0x00);
	wmb();
	dac_write(par, BT459_CMAP, red);
	wmb();
	dac_write(par, BT459_CMAP, green);
	wmb();
	dac_write(par, BT459_CMAP, blue);

	return 0;
}