#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  unsigned int u16 ;
struct iga_par {int dummy; } ;
struct TYPE_4__ {int bits_per_pixel; } ;
struct TYPE_3__ {unsigned int len; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_2__ var; TYPE_1__ cmap; scalar_t__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_DATA ; 
 int /*<<< orphan*/  DAC_W_INDEX ; 
 int /*<<< orphan*/  pci_outb (struct iga_par*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int igafb_setcolreg(unsigned regno, unsigned red, unsigned green,
                           unsigned blue, unsigned transp,
                           struct fb_info *info)
{
        /*
         *  Set a single color register. The values supplied are
         *  already rounded down to the hardware's capabilities
         *  (according to the entries in the `var' structure). Return
         *  != 0 for invalid regno.
         */
	struct iga_par *par = (struct iga_par *)info->par;

        if (regno >= info->cmap.len)
                return 1;

	pci_outb(par, regno, DAC_W_INDEX);
	pci_outb(par, red,   DAC_DATA);
	pci_outb(par, green, DAC_DATA);
	pci_outb(par, blue,  DAC_DATA);

	if (regno < 16) {
		switch (info->var.bits_per_pixel) {
		case 16:
			((u16*)(info->pseudo_palette))[regno] = 
				(regno << 10) | (regno << 5) | regno;
			break;
		case 24:
			((u32*)(info->pseudo_palette))[regno] = 
				(regno << 16) | (regno << 8) | regno;
		break;
		case 32:
			{ int i;
			i = (regno << 8) | regno;
			((u32*)(info->pseudo_palette))[regno] = (i << 16) | i;
			}
			break;
		}
	}
	return 0;
}