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
typedef  unsigned int u32 ;
struct tga_par {scalar_t__ tga_type; int /*<<< orphan*/  dev; } ;
struct fb_info {scalar_t__ pseudo_palette; scalar_t__ par; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT459_LOAD_ADDR (struct tga_par*,unsigned int) ; 
 int BT459_PALETTE ; 
 int /*<<< orphan*/  BT463_LOAD_ADDR (struct tga_par*,unsigned int) ; 
 int BT463_PALETTE ; 
 int /*<<< orphan*/  BT485_ADDR_PAL_WRITE ; 
 int BT485_DATA_PAL ; 
 int /*<<< orphan*/  BT485_WRITE (struct tga_par*,unsigned int,int /*<<< orphan*/ ) ; 
 int TGA_BUS_PCI (int /*<<< orphan*/ ) ; 
 int TGA_BUS_TC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TGA_RAMDAC_REG ; 
 int /*<<< orphan*/  TGA_RAMDAC_SETUP_REG ; 
 scalar_t__ TGA_TYPE_8PLANE ; 
 int /*<<< orphan*/  TGA_WRITE_REG (struct tga_par*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tgafb_setcolreg(unsigned regno, unsigned red, unsigned green, unsigned blue,
		unsigned transp, struct fb_info *info)
{
	struct tga_par *par = (struct tga_par *) info->par;
	int tga_bus_pci = TGA_BUS_PCI(par->dev);
	int tga_bus_tc = TGA_BUS_TC(par->dev);

	if (regno > 255)
		return 1;
	red >>= 8;
	green >>= 8;
	blue >>= 8;

	if (par->tga_type == TGA_TYPE_8PLANE && tga_bus_pci) {
		BT485_WRITE(par, regno, BT485_ADDR_PAL_WRITE);
		TGA_WRITE_REG(par, BT485_DATA_PAL, TGA_RAMDAC_SETUP_REG);
		TGA_WRITE_REG(par, red|(BT485_DATA_PAL<<8),TGA_RAMDAC_REG);
		TGA_WRITE_REG(par, green|(BT485_DATA_PAL<<8),TGA_RAMDAC_REG);
		TGA_WRITE_REG(par, blue|(BT485_DATA_PAL<<8),TGA_RAMDAC_REG);
	} else if (par->tga_type == TGA_TYPE_8PLANE && tga_bus_tc) {
		BT459_LOAD_ADDR(par, regno);
		TGA_WRITE_REG(par, BT459_PALETTE << 2, TGA_RAMDAC_SETUP_REG);
		TGA_WRITE_REG(par, red, TGA_RAMDAC_REG);
		TGA_WRITE_REG(par, green, TGA_RAMDAC_REG);
		TGA_WRITE_REG(par, blue, TGA_RAMDAC_REG);
	} else {
		if (regno < 16) {
			u32 value = (regno << 16) | (regno << 8) | regno;
			((u32 *)info->pseudo_palette)[regno] = value;
		}
		BT463_LOAD_ADDR(par, regno);
		TGA_WRITE_REG(par, BT463_PALETTE << 2, TGA_RAMDAC_SETUP_REG);
		TGA_WRITE_REG(par, red, TGA_RAMDAC_REG);
		TGA_WRITE_REG(par, green, TGA_RAMDAC_REG);
		TGA_WRITE_REG(par, blue, TGA_RAMDAC_REG);
	}

	return 0;
}