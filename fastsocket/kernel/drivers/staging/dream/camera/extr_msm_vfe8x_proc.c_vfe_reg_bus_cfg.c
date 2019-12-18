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
typedef  void* uint32_t ;
struct vfe_bus_cfg_data {scalar_t__ rawWritePathSelect; scalar_t__ rawPixelDataSize; int /*<<< orphan*/  viewCbcrWrPathEn; int /*<<< orphan*/  viewYWrPathEn; int /*<<< orphan*/  encCbcrWrPathEn; int /*<<< orphan*/  encYWrPathEn; int /*<<< orphan*/  stripeRdPathEn; } ;
struct vfe_axi_bus_cfg {void* rawWritePathSelect; void* rawPixelDataSize; int /*<<< orphan*/  viewCbcrWrPathEn; int /*<<< orphan*/  viewYWrPathEn; int /*<<< orphan*/  encCbcrWrPathEn; int /*<<< orphan*/  encYWrPathEn; int /*<<< orphan*/  stripeRdPathEn; } ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_BUS_CFG ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  writel (void*,scalar_t__) ; 

__attribute__((used)) static void vfe_reg_bus_cfg(struct vfe_bus_cfg_data *in)
{
	struct vfe_axi_bus_cfg cmd;

	cmd.stripeRdPathEn      = in->stripeRdPathEn;
	cmd.encYWrPathEn        = in->encYWrPathEn;
	cmd.encCbcrWrPathEn     = in->encCbcrWrPathEn;
	cmd.viewYWrPathEn       = in->viewYWrPathEn;
	cmd.viewCbcrWrPathEn    = in->viewCbcrWrPathEn;
	cmd.rawPixelDataSize    = (uint32_t)in->rawPixelDataSize;
	cmd.rawWritePathSelect  = (uint32_t)in->rawWritePathSelect;

	/*  program vfe_bus_cfg */
	writel(*((uint32_t *)&cmd), ctrl->vfebase + VFE_BUS_CFG);
}