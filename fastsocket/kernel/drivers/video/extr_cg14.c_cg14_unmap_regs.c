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
struct of_device {int /*<<< orphan*/ * resource; } ;
struct TYPE_2__ {int smem_len; } ;
struct fb_info {TYPE_1__ fix; scalar_t__ screen_base; } ;
struct cg14_regs {int dummy; } ;
struct cg14_par {scalar_t__ cursor; scalar_t__ clut; scalar_t__ regs; } ;
struct cg14_cursor {int dummy; } ;
struct cg14_clut {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void cg14_unmap_regs(struct of_device *op, struct fb_info *info,
			    struct cg14_par *par)
{
	if (par->regs)
		of_iounmap(&op->resource[0],
			   par->regs, sizeof(struct cg14_regs));
	if (par->clut)
		of_iounmap(&op->resource[0],
			   par->clut, sizeof(struct cg14_clut));
	if (par->cursor)
		of_iounmap(&op->resource[0],
			   par->cursor, sizeof(struct cg14_cursor));
	if (info->screen_base)
		of_iounmap(&op->resource[1],
			   info->screen_base, info->fix.smem_len);
}