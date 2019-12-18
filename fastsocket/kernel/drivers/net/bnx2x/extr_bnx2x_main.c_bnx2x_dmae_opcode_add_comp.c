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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int DMAE_CMD_C_ENABLE ; 
 int DMAE_COMMAND_C_DST_SHIFT ; 

u32 bnx2x_dmae_opcode_add_comp(u32 opcode, u8 comp_type)
{
	return opcode | ((comp_type << DMAE_COMMAND_C_DST_SHIFT) |
			   DMAE_CMD_C_ENABLE);
}