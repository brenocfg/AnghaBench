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
typedef  int u_int ;
struct TYPE_4__ {int cmode; } ;
struct fb_info_control {int* pseudo_palette; TYPE_2__ par; TYPE_1__* cmap_regs; } ;
struct fb_info {int dummy; } ;
typedef  int __u8 ;
struct TYPE_3__ {int /*<<< orphan*/  lut; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
#define  CMODE_16 129 
#define  CMODE_32 128 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int controlfb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			     u_int transp, struct fb_info *info)
{
	struct fb_info_control *p = (struct fb_info_control *) info;
	__u8 r, g, b;

	if (regno > 255)
		return 1;

	r = red >> 8;
	g = green >> 8;
	b = blue >> 8;

	out_8(&p->cmap_regs->addr, regno);	/* tell clut what addr to fill	*/
	out_8(&p->cmap_regs->lut, r);		/* send one color channel at	*/
	out_8(&p->cmap_regs->lut, g);		/* a time...			*/
	out_8(&p->cmap_regs->lut, b);

	if (regno < 16) {
		int i;
		switch (p->par.cmode) {
		case CMODE_16:
			p->pseudo_palette[regno] =
			    (regno << 10) | (regno << 5) | regno;
			break;
		case CMODE_32:
			i = (regno << 8) | regno;
			p->pseudo_palette[regno] = (i << 16) | i;
			break;
		}
	}

	return 0;
}