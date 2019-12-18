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
struct gxt4500_par {int pixfmt; } ;
struct fb_info {unsigned int* pseudo_palette; struct gxt4500_par* par; } ;

/* Variables and functions */
 scalar_t__ CMAP ; 
#define  DFA_PIX_16BIT_1555 131 
#define  DFA_PIX_16BIT_565 130 
#define  DFA_PIX_24BIT 129 
#define  DFA_PIX_32BIT 128 
 int DFA_PIX_8BIT ; 
 int /*<<< orphan*/  writereg (struct gxt4500_par*,scalar_t__,unsigned int) ; 

__attribute__((used)) static int gxt4500_setcolreg(unsigned int reg, unsigned int red,
			     unsigned int green, unsigned int blue,
			     unsigned int transp, struct fb_info *info)
{
	u32 cmap_entry;
	struct gxt4500_par *par = info->par;

	if (reg > 1023)
		return 1;
	cmap_entry = ((transp & 0xff00) << 16) | ((red & 0xff00) << 8) |
		(green & 0xff00) | (blue >> 8);
	writereg(par, CMAP + reg * 4, cmap_entry);

	if (reg < 16 && par->pixfmt != DFA_PIX_8BIT) {
		u32 *pal = info->pseudo_palette;
		u32 val = reg;
		switch (par->pixfmt) {
		case DFA_PIX_16BIT_565:
			val |= (reg << 11) | (reg << 6);
			break;
		case DFA_PIX_16BIT_1555:
			val |= (reg << 10) | (reg << 5);
			break;
		case DFA_PIX_32BIT:
			val |= (reg << 24);
			/* fall through */
		case DFA_PIX_24BIT:
			val |= (reg << 16) | (reg << 8);
			break;
		}
		pal[reg] = val;
	}

	return 0;
}