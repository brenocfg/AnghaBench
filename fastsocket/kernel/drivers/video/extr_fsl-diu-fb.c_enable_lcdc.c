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
struct mfb_info {struct fsl_diu_data* parent; } ;
struct fsl_diu_data {int /*<<< orphan*/  fb_enabled; } ;
struct fb_info {struct mfb_info* par; } ;
struct diu {int /*<<< orphan*/  diu_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; struct diu* diu_reg; } ;

/* Variables and functions */
 TYPE_1__ dr ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_lcdc(struct fb_info *info)
{
	struct diu *hw = dr.diu_reg;
	struct mfb_info *mfbi = info->par;
	struct fsl_diu_data *machine_data = mfbi->parent;

	if (!machine_data->fb_enabled) {
		out_be32(&hw->diu_mode, dr.mode);
		machine_data->fb_enabled++;
	}
}