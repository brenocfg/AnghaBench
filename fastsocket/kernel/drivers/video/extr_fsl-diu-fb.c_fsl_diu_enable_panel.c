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
struct mfb_info {int index; scalar_t__ type; struct diu_ad* ad; int /*<<< orphan*/  count; struct fsl_diu_data* parent; } ;
struct fsl_diu_data {TYPE_2__* dummy_ad; TYPE_1__** fsl_diu_info; } ;
struct fb_info {struct mfb_info* par; } ;
struct diu_ad {int /*<<< orphan*/  paddr; void* next_ad; } ;
struct diu {int /*<<< orphan*/ * desc; } ;
struct TYPE_6__ {struct diu* diu_reg; } ;
struct TYPE_5__ {int /*<<< orphan*/  paddr; } ;
struct TYPE_4__ {struct mfb_info* par; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MFB_TYPE_OFF ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 TYPE_3__ dr ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int fsl_diu_enable_panel(struct fb_info *info)
{
	struct mfb_info *pmfbi, *cmfbi, *mfbi = info->par;
	struct diu *hw = dr.diu_reg;
	struct diu_ad *ad = mfbi->ad;
	struct fsl_diu_data *machine_data = mfbi->parent;
	int res = 0;

	pr_debug("enable_panel index %d\n", mfbi->index);
	if (mfbi->type != MFB_TYPE_OFF) {
		switch (mfbi->index) {
		case 0:				/* plane 0 */
			if (hw->desc[0] != ad->paddr)
				out_be32(&hw->desc[0], ad->paddr);
			break;
		case 1:				/* plane 1 AOI 0 */
			cmfbi = machine_data->fsl_diu_info[2]->par;
			if (hw->desc[1] != ad->paddr) {	/* AOI0 closed */
				if (cmfbi->count > 0)	/* AOI1 open */
					ad->next_ad =
						cpu_to_le32(cmfbi->ad->paddr);
				else
					ad->next_ad = 0;
				out_be32(&hw->desc[1], ad->paddr);
			}
			break;
		case 3:				/* plane 2 AOI 0 */
			cmfbi = machine_data->fsl_diu_info[4]->par;
			if (hw->desc[2] != ad->paddr) {	/* AOI0 closed */
				if (cmfbi->count > 0)	/* AOI1 open */
					ad->next_ad =
						cpu_to_le32(cmfbi->ad->paddr);
				else
					ad->next_ad = 0;
				out_be32(&hw->desc[2], ad->paddr);
			}
			break;
		case 2:				/* plane 1 AOI 1 */
			pmfbi = machine_data->fsl_diu_info[1]->par;
			ad->next_ad = 0;
			if (hw->desc[1] == machine_data->dummy_ad->paddr)
				out_be32(&hw->desc[1], ad->paddr);
			else					/* AOI0 open */
				pmfbi->ad->next_ad = cpu_to_le32(ad->paddr);
			break;
		case 4:				/* plane 2 AOI 1 */
			pmfbi = machine_data->fsl_diu_info[3]->par;
			ad->next_ad = 0;
			if (hw->desc[2] == machine_data->dummy_ad->paddr)
				out_be32(&hw->desc[2], ad->paddr);
			else				/* AOI0 was open */
				pmfbi->ad->next_ad = cpu_to_le32(ad->paddr);
			break;
		default:
			res = -EINVAL;
			break;
		}
	} else
		res = -EINVAL;
	return res;
}