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
typedef  size_t u32 ;
struct TYPE_2__ {scalar_t__ last_cb_index; struct command_block* cb_list; } ;
struct ipw_priv {TYPE_1__ sram_desc; } ;
struct command_block {size_t status; size_t dest_addr; size_t source_addr; size_t control; } ;

/* Variables and functions */
 size_t CB_DEST_AUTOINC ; 
 size_t CB_DEST_LE ; 
 size_t CB_DEST_SIZE_LONG ; 
 size_t CB_INT_ENABLED ; 
 size_t CB_LAST_VALID ; 
 scalar_t__ CB_NUMBER_OF_ELEMENTS_SMALL ; 
 size_t CB_SRC_AUTOINC ; 
 size_t CB_SRC_IO_GATED ; 
 size_t CB_SRC_LE ; 
 size_t CB_SRC_SIZE_LONG ; 
 size_t CB_VALID ; 
 int /*<<< orphan*/  IPW_DEBUG_FW_INFO (char*,size_t,size_t,size_t) ; 

__attribute__((used)) static int ipw_fw_dma_add_command_block(struct ipw_priv *priv,
					u32 src_address,
					u32 dest_address,
					u32 length,
					int interrupt_enabled, int is_last)
{

	u32 control = CB_VALID | CB_SRC_LE | CB_DEST_LE | CB_SRC_AUTOINC |
	    CB_SRC_IO_GATED | CB_DEST_AUTOINC | CB_SRC_SIZE_LONG |
	    CB_DEST_SIZE_LONG;
	struct command_block *cb;
	u32 last_cb_element = 0;

	IPW_DEBUG_FW_INFO("src_address=0x%x dest_address=0x%x length=0x%x\n",
			  src_address, dest_address, length);

	if (priv->sram_desc.last_cb_index >= CB_NUMBER_OF_ELEMENTS_SMALL)
		return -1;

	last_cb_element = priv->sram_desc.last_cb_index;
	cb = &priv->sram_desc.cb_list[last_cb_element];
	priv->sram_desc.last_cb_index++;

	/* Calculate the new CB control word */
	if (interrupt_enabled)
		control |= CB_INT_ENABLED;

	if (is_last)
		control |= CB_LAST_VALID;

	control |= length;

	/* Calculate the CB Element's checksum value */
	cb->status = control ^ src_address ^ dest_address;

	/* Copy the Source and Destination addresses */
	cb->dest_addr = dest_address;
	cb->source_addr = src_address;

	/* Copy the Control Word last */
	cb->control = control;

	return 0;
}