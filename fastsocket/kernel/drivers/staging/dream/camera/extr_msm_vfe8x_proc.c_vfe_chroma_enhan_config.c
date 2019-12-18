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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_color_convert_cfg {int /*<<< orphan*/  ConvertOffset; int /*<<< orphan*/  v2; int /*<<< orphan*/  v1; int /*<<< orphan*/  v0; int /*<<< orphan*/  kcr; int /*<<< orphan*/  kcb; int /*<<< orphan*/  dm; int /*<<< orphan*/  dp; int /*<<< orphan*/  cm; int /*<<< orphan*/  cp; int /*<<< orphan*/  bm; int /*<<< orphan*/  bp; int /*<<< orphan*/  am; int /*<<< orphan*/  ap; } ;
struct vfe_cmd_chroma_enhan_config {int /*<<< orphan*/  RGBtoYConversionOffset; int /*<<< orphan*/  RGBtoYConversionV2; int /*<<< orphan*/  RGBtoYConversionV1; int /*<<< orphan*/  RGBtoYConversionV0; int /*<<< orphan*/  kcr; int /*<<< orphan*/  kcb; int /*<<< orphan*/  dm; int /*<<< orphan*/  dp; int /*<<< orphan*/  cm; int /*<<< orphan*/  cp; int /*<<< orphan*/  bm; int /*<<< orphan*/  bp; int /*<<< orphan*/  am; int /*<<< orphan*/  ap; int /*<<< orphan*/  enable; } ;
struct vfe_chroma_enhance_cfg {int /*<<< orphan*/  ConvertOffset; int /*<<< orphan*/  v2; int /*<<< orphan*/  v1; int /*<<< orphan*/  v0; int /*<<< orphan*/  kcr; int /*<<< orphan*/  kcb; int /*<<< orphan*/  dm; int /*<<< orphan*/  dp; int /*<<< orphan*/  cm; int /*<<< orphan*/  cp; int /*<<< orphan*/  bm; int /*<<< orphan*/  bp; int /*<<< orphan*/  am; int /*<<< orphan*/  ap; } ;
typedef  int /*<<< orphan*/  cmd2 ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int /*<<< orphan*/  chromaEnhanEnable; } ;
struct TYPE_4__ {scalar_t__ vfebase; TYPE_1__ vfeModuleEnableLocal; } ;

/* Variables and functions */
 scalar_t__ VFE_CHROMA_ENHAN_A ; 
 scalar_t__ VFE_COLOR_CONVERT_COEFF_0 ; 
 TYPE_2__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_color_convert_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_chroma_enhan_config(struct vfe_cmd_chroma_enhan_config *in)
{
	struct vfe_chroma_enhance_cfg cmd;
	struct vfe_color_convert_cfg cmd2;

	memset(&cmd, 0, sizeof(cmd));
	memset(&cmd2, 0, sizeof(cmd2));

	ctrl->vfeModuleEnableLocal.chromaEnhanEnable = in->enable;

	cmd.ap             = in->ap;
	cmd.am             = in->am;
	cmd.bp             = in->bp;
	cmd.bm             = in->bm;
	cmd.cp             = in->cp;
	cmd.cm             = in->cm;
	cmd.dp             = in->dp;
	cmd.dm             = in->dm;
	cmd.kcb            = in->kcb;
	cmd.kcr            = in->kcr;

	cmd2.v0            = in->RGBtoYConversionV0;
	cmd2.v1            = in->RGBtoYConversionV1;
	cmd2.v2            = in->RGBtoYConversionV2;
	cmd2.ConvertOffset = in->RGBtoYConversionOffset;

	vfe_prog_hw(ctrl->vfebase + VFE_CHROMA_ENHAN_A,
		(uint32_t *)&cmd, sizeof(cmd));

	vfe_prog_hw(ctrl->vfebase + VFE_COLOR_CONVERT_COEFF_0,
		(uint32_t *)&cmd2, sizeof(cmd2));
}