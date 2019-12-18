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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/ * hwRegPongAddress; int /*<<< orphan*/ * hwRegPingAddress; } ;
struct TYPE_4__ {int /*<<< orphan*/ * hwRegPongAddress; int /*<<< orphan*/ * hwRegPingAddress; } ;
struct vfe_output_path_combo {TYPE_2__ cbcrPath; TYPE_1__ yPath; } ;
struct TYPE_6__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_BUS_ENC_CBCR_WR_PING_ADDR ; 
 scalar_t__ VFE_BUS_ENC_CBCR_WR_PONG_ADDR ; 
 scalar_t__ VFE_BUS_ENC_Y_WR_PING_ADDR ; 
 scalar_t__ VFE_BUS_ENC_Y_WR_PONG_ADDR ; 
 scalar_t__ VFE_BUS_VIEW_CBCR_WR_PING_ADDR ; 
 scalar_t__ VFE_BUS_VIEW_CBCR_WR_PONG_ADDR ; 
 scalar_t__ VFE_BUS_VIEW_Y_WR_PING_ADDR ; 
 scalar_t__ VFE_BUS_VIEW_Y_WR_PONG_ADDR ; 
 TYPE_3__* ctrl ; 

__attribute__((used)) static void
vfe_set_bus_pipo_addr(struct vfe_output_path_combo *vpath,
	struct vfe_output_path_combo *epath)
{
	vpath->yPath.hwRegPingAddress = (uint8_t *)
		(ctrl->vfebase + VFE_BUS_VIEW_Y_WR_PING_ADDR);
	vpath->yPath.hwRegPongAddress = (uint8_t *)
		(ctrl->vfebase + VFE_BUS_VIEW_Y_WR_PONG_ADDR);
	vpath->cbcrPath.hwRegPingAddress = (uint8_t *)
		(ctrl->vfebase + VFE_BUS_VIEW_CBCR_WR_PING_ADDR);
	vpath->cbcrPath.hwRegPongAddress = (uint8_t *)
		(ctrl->vfebase + VFE_BUS_VIEW_CBCR_WR_PONG_ADDR);

	epath->yPath.hwRegPingAddress = (uint8_t *)
		(ctrl->vfebase + VFE_BUS_ENC_Y_WR_PING_ADDR);
	epath->yPath.hwRegPongAddress = (uint8_t *)
		(ctrl->vfebase + VFE_BUS_ENC_Y_WR_PONG_ADDR);
	epath->cbcrPath.hwRegPingAddress = (uint8_t *)
		(ctrl->vfebase + VFE_BUS_ENC_CBCR_WR_PING_ADDR);
	epath->cbcrPath.hwRegPongAddress = (uint8_t *)
		(ctrl->vfebase + VFE_BUS_ENC_CBCR_WR_PONG_ADDR);
}