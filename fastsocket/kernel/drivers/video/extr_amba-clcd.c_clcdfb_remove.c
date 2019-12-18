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
struct TYPE_6__ {scalar_t__ len; } ;
struct TYPE_5__ {TYPE_3__ cmap; } ;
struct clcd_fb {TYPE_1__* board; int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; TYPE_2__ fb; } ;
struct amba_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* remove ) (struct clcd_fb*) ;} ;

/* Variables and functions */
 struct clcd_fb* amba_get_drvdata (struct amba_device*) ; 
 int /*<<< orphan*/  amba_release_regions (struct amba_device*) ; 
 int /*<<< orphan*/  amba_set_drvdata (struct amba_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clcdfb_disable (struct clcd_fb*) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fb_dealloc_cmap (TYPE_3__*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct clcd_fb*) ; 
 int /*<<< orphan*/  stub1 (struct clcd_fb*) ; 
 int /*<<< orphan*/  unregister_framebuffer (TYPE_2__*) ; 

__attribute__((used)) static int clcdfb_remove(struct amba_device *dev)
{
	struct clcd_fb *fb = amba_get_drvdata(dev);

	amba_set_drvdata(dev, NULL);

	clcdfb_disable(fb);
	unregister_framebuffer(&fb->fb);
	if (fb->fb.cmap.len)
		fb_dealloc_cmap(&fb->fb.cmap);
	iounmap(fb->regs);
	clk_put(fb->clk);

	fb->board->remove(fb);

	kfree(fb);

	amba_release_regions(dev);

	return 0;
}