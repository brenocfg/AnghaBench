#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_FW (char*) ; 
 int /*<<< orphan*/  IPW_DEBUG_FW_INFO (char*,int) ; 
 int IPW_DMA_I_CURRENT_CB ; 
 int IPW_DMA_I_DMA_CONTROL ; 
 int ipw_read_reg32 (struct ipw_priv*,int) ; 

__attribute__((used)) static void ipw_fw_dma_dump_command_block(struct ipw_priv *priv)
{
	u32 address;
	u32 register_value = 0;
	u32 cb_fields_address = 0;

	IPW_DEBUG_FW(">> :\n");
	address = ipw_read_reg32(priv, IPW_DMA_I_CURRENT_CB);
	IPW_DEBUG_FW_INFO("Current CB is 0x%x\n", address);

	/* Read the DMA Controlor register */
	register_value = ipw_read_reg32(priv, IPW_DMA_I_DMA_CONTROL);
	IPW_DEBUG_FW_INFO("IPW_DMA_I_DMA_CONTROL is 0x%x\n", register_value);

	/* Print the CB values */
	cb_fields_address = address;
	register_value = ipw_read_reg32(priv, cb_fields_address);
	IPW_DEBUG_FW_INFO("Current CB Control Field is 0x%x\n", register_value);

	cb_fields_address += sizeof(u32);
	register_value = ipw_read_reg32(priv, cb_fields_address);
	IPW_DEBUG_FW_INFO("Current CB Source Field is 0x%x\n", register_value);

	cb_fields_address += sizeof(u32);
	register_value = ipw_read_reg32(priv, cb_fields_address);
	IPW_DEBUG_FW_INFO("Current CB Destination Field is 0x%x\n",
			  register_value);

	cb_fields_address += sizeof(u32);
	register_value = ipw_read_reg32(priv, cb_fields_address);
	IPW_DEBUG_FW_INFO("Current CB Status Field is 0x%x\n", register_value);

	IPW_DEBUG_FW(">> :\n");
}