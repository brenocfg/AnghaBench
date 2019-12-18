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
struct TYPE_3__ {int /*<<< orphan*/  misrEnable; int /*<<< orphan*/  binningEnable; int /*<<< orphan*/  irqSubSampleEnable; int /*<<< orphan*/  busSubSampleEnable; int /*<<< orphan*/  vfeSubSampleEnable; int /*<<< orphan*/  syncMode; int /*<<< orphan*/  hSyncEdge; int /*<<< orphan*/  vSyncEdge; } ;
struct vfe_camif_cfg_data {TYPE_1__ camifCfgFromCmd; int /*<<< orphan*/  camif2BusEnable; int /*<<< orphan*/  camif2OutputEnable; } ;
struct VFE_CAMIFConfigType {int /*<<< orphan*/  misrEnable; int /*<<< orphan*/  binningEnable; int /*<<< orphan*/  irqSubsampleEnable; int /*<<< orphan*/  camif2busEnable; int /*<<< orphan*/  camif2vfeEnable; int /*<<< orphan*/  busSubsampleEnable; int /*<<< orphan*/  vfeSubsampleEnable; int /*<<< orphan*/  syncMode; int /*<<< orphan*/  HSyncEdge; int /*<<< orphan*/  VSyncEdge; } ;
typedef  int /*<<< orphan*/  cfg ;
struct TYPE_4__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ CAMIF_CONFIG ; 
 TYPE_2__* ctrl ; 
 int /*<<< orphan*/  memset (struct VFE_CAMIFConfigType*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vfe_reg_camif_config(struct vfe_camif_cfg_data *in)
{
	struct VFE_CAMIFConfigType cfg;

	memset(&cfg, 0, sizeof(cfg));

	cfg.VSyncEdge          =
		in->camifCfgFromCmd.vSyncEdge;

	cfg.HSyncEdge          =
		in->camifCfgFromCmd.hSyncEdge;

	cfg.syncMode           =
		in->camifCfgFromCmd.syncMode;

	cfg.vfeSubsampleEnable =
		in->camifCfgFromCmd.vfeSubSampleEnable;

	cfg.busSubsampleEnable =
		in->camifCfgFromCmd.busSubSampleEnable;

	cfg.camif2vfeEnable    =
		in->camif2OutputEnable;

	cfg.camif2busEnable    =
		in->camif2BusEnable;

	cfg.irqSubsampleEnable =
		in->camifCfgFromCmd.irqSubSampleEnable;

	cfg.binningEnable      =
		in->camifCfgFromCmd.binningEnable;

	cfg.misrEnable         =
		in->camifCfgFromCmd.misrEnable;

	/*  program camif_config */
	writel(*((uint32_t *)&cfg), ctrl->vfebase + CAMIF_CONFIG);
}