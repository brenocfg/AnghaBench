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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ last_cb_index; } ;
struct ipw_priv {TYPE_1__ sram_desc; } ;

/* Variables and functions */
 int DMA_CB_STOP_AND_ABORT ; 
 int DMA_CONTROL_SMALL_CB_CONST_VALUE ; 
 int /*<<< orphan*/  IPW_DEBUG_FW (char*) ; 
 int /*<<< orphan*/  IPW_DMA_I_DMA_CONTROL ; 
 int /*<<< orphan*/  ipw_write_reg32 (struct ipw_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ipw_fw_dma_abort(struct ipw_priv *priv)
{
	u32 control = 0;

	IPW_DEBUG_FW(">> :\n");

	/* set the Stop and Abort bit */
	control = DMA_CONTROL_SMALL_CB_CONST_VALUE | DMA_CB_STOP_AND_ABORT;
	ipw_write_reg32(priv, IPW_DMA_I_DMA_CONTROL, control);
	priv->sram_desc.last_cb_index = 0;

	IPW_DEBUG_FW("<<\n");
}