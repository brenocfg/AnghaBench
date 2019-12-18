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
struct vfe_cmd_chroma_suppression_config {int /*<<< orphan*/  nn1; int /*<<< orphan*/  mm1; int /*<<< orphan*/  n3; int /*<<< orphan*/  n1; int /*<<< orphan*/  m3; int /*<<< orphan*/  m1; int /*<<< orphan*/  enable; } ;
struct vfe_chroma_suppress_cfg {int /*<<< orphan*/  nn1; int /*<<< orphan*/  mm1; int /*<<< orphan*/  n3; int /*<<< orphan*/  n1; int /*<<< orphan*/  m3; int /*<<< orphan*/  m1; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int /*<<< orphan*/  chromaSuppressionEnable; } ;
struct TYPE_4__ {scalar_t__ vfebase; TYPE_1__ vfeModuleEnableLocal; } ;

/* Variables and functions */
 scalar_t__ VFE_CHROMA_SUPPRESS_CFG_0 ; 
 TYPE_2__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_chroma_suppress_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_chroma_sup_config(struct vfe_cmd_chroma_suppression_config *in)
{
	struct vfe_chroma_suppress_cfg cmd;
	memset(&cmd, 0, sizeof(cmd));

	ctrl->vfeModuleEnableLocal.chromaSuppressionEnable = in->enable;

	cmd.m1  = in->m1;
	cmd.m3  = in->m3;
	cmd.n1  = in->n1;
	cmd.n3  = in->n3;
	cmd.mm1 = in->mm1;
	cmd.nn1 = in->nn1;

	vfe_prog_hw(ctrl->vfebase + VFE_CHROMA_SUPPRESS_CFG_0,
		(uint32_t *)&cmd, sizeof(cmd));
}