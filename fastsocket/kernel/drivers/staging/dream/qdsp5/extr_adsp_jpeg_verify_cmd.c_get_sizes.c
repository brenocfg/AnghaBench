#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int process_cfg; int ip_size_cfg; int frag_cfg; } ;
typedef  TYPE_1__ jpeg_cmd_enc_cfg ;

/* Variables and functions */
 int JPEG_CMD_ENC_PROCESS_CFG_IP_DATA_FORMAT_H2V2 ; 
 int JPEG_CMD_ENC_PROCESS_CFG_IP_DATA_FORMAT_M ; 
 int JPEG_CMD_FRAG_SIZE_LUMA_HEIGHT_M ; 
 int JPEG_CMD_IP_SIZE_CFG_LUMA_WIDTH_M ; 

__attribute__((used)) static inline void get_sizes(jpeg_cmd_enc_cfg *cmd, uint32_t *luma_size,
			     uint32_t *chroma_size)
{
	uint32_t fmt, luma_width, luma_height;

	fmt = cmd->process_cfg & JPEG_CMD_ENC_PROCESS_CFG_IP_DATA_FORMAT_M;
	luma_width = (cmd->ip_size_cfg & JPEG_CMD_IP_SIZE_CFG_LUMA_WIDTH_M)
		      >> 16;
	luma_height = cmd->frag_cfg & JPEG_CMD_FRAG_SIZE_LUMA_HEIGHT_M;
	*luma_size = luma_width * luma_height;
	if (fmt == JPEG_CMD_ENC_PROCESS_CFG_IP_DATA_FORMAT_H2V2)
		*chroma_size = *luma_size/2;
	else
		*chroma_size = *luma_size;
}