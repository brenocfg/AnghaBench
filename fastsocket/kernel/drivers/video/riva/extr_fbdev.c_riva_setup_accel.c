#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* Clip; } ;
struct riva_par {TYPE_3__ riva; } ;
struct TYPE_4__ {int xres_virtual; int yres_virtual; } ;
struct fb_info {TYPE_1__ var; struct riva_par* par; } ;
struct TYPE_5__ {int /*<<< orphan*/  WidthHeight; int /*<<< orphan*/  TopLeft; } ;

/* Variables and functions */
 int /*<<< orphan*/  Clip ; 
 int /*<<< orphan*/  NV_WR32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RIVA_FIFO_FREE (TYPE_3__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  riva_set_rop_solid (struct riva_par*,int) ; 
 int /*<<< orphan*/  wait_for_idle (struct riva_par*) ; 

__attribute__((used)) static void riva_setup_accel(struct fb_info *info)
{
	struct riva_par *par = info->par;

	RIVA_FIFO_FREE(par->riva, Clip, 2);
	NV_WR32(&par->riva.Clip->TopLeft, 0, 0x0);
	NV_WR32(&par->riva.Clip->WidthHeight, 0,
		(info->var.xres_virtual & 0xffff) |
		(info->var.yres_virtual << 16));
	riva_set_rop_solid(par, 0xcc);
	wait_for_idle(par);
}