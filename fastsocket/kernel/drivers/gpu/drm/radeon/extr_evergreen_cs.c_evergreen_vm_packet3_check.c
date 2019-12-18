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
typedef  size_t u32 ;
struct radeon_device {int dummy; } ;
struct radeon_cs_packet {size_t idx; int opcode; int count; } ;

/* Variables and functions */
#define  CAYMAN_PACKET3_DEALLOC_STATE 173 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
#define  PACKET3_CLEAR_STATE 172 
#define  PACKET3_COND_EXEC 171 
#define  PACKET3_COND_WRITE 170 
#define  PACKET3_CONTEXT_CONTROL 169 
#define  PACKET3_COPY_DW 168 
#define  PACKET3_CP_DMA 167 
 size_t PACKET3_CP_DMA_CMD_DAIC ; 
 size_t PACKET3_CP_DMA_CMD_DAS ; 
 size_t PACKET3_CP_DMA_CMD_SAIC ; 
 size_t PACKET3_CP_DMA_CMD_SAS ; 
#define  PACKET3_DISPATCH_DIRECT 166 
#define  PACKET3_DISPATCH_INDIRECT 165 
#define  PACKET3_DRAW_INDEX 164 
#define  PACKET3_DRAW_INDEX_2 163 
#define  PACKET3_DRAW_INDEX_AUTO 162 
#define  PACKET3_DRAW_INDEX_IMMD 161 
#define  PACKET3_DRAW_INDEX_INDIRECT 160 
#define  PACKET3_DRAW_INDEX_MULTI_AUTO 159 
#define  PACKET3_DRAW_INDEX_MULTI_ELEMENT 158 
#define  PACKET3_DRAW_INDEX_OFFSET 157 
#define  PACKET3_DRAW_INDEX_OFFSET_2 156 
#define  PACKET3_DRAW_INDIRECT 155 
#define  PACKET3_EVENT_WRITE 154 
#define  PACKET3_EVENT_WRITE_EOP 153 
#define  PACKET3_EVENT_WRITE_EOS 152 
#define  PACKET3_INDEX_BASE 151 
#define  PACKET3_INDEX_BUFFER_SIZE 150 
#define  PACKET3_INDEX_TYPE 149 
#define  PACKET3_MEM_WRITE 148 
#define  PACKET3_MODE_CONTROL 147 
#define  PACKET3_MPEG_INDEX 146 
#define  PACKET3_NOP 145 
#define  PACKET3_NUM_INSTANCES 144 
#define  PACKET3_PRED_EXEC 143 
#define  PACKET3_SET_BASE 142 
#define  PACKET3_SET_BOOL_CONST 141 
#define  PACKET3_SET_CONFIG_REG 140 
 size_t PACKET3_SET_CONFIG_REG_END ; 
 size_t PACKET3_SET_CONFIG_REG_START ; 
#define  PACKET3_SET_CONTEXT_REG 139 
#define  PACKET3_SET_CONTEXT_REG_INDIRECT 138 
#define  PACKET3_SET_CTL_CONST 137 
#define  PACKET3_SET_LOOP_CONST 136 
#define  PACKET3_SET_PREDICATION 135 
#define  PACKET3_SET_RESOURCE 134 
#define  PACKET3_SET_RESOURCE_INDIRECT 133 
#define  PACKET3_SET_RESOURCE_OFFSET 132 
#define  PACKET3_SET_SAMPLER 131 
#define  PACKET3_STRMOUT_BUFFER_UPDATE 130 
#define  PACKET3_SURFACE_SYNC 129 
#define  PACKET3_WAIT_REG_MEM 128 
 int /*<<< orphan*/  evergreen_vm_reg_valid (size_t) ; 

__attribute__((used)) static int evergreen_vm_packet3_check(struct radeon_device *rdev,
				      u32 *ib, struct radeon_cs_packet *pkt)
{
	u32 idx = pkt->idx + 1;
	u32 idx_value = ib[idx];
	u32 start_reg, end_reg, reg, i;
	u32 command, info;

	switch (pkt->opcode) {
	case PACKET3_NOP:
	case PACKET3_SET_BASE:
	case PACKET3_CLEAR_STATE:
	case PACKET3_INDEX_BUFFER_SIZE:
	case PACKET3_DISPATCH_DIRECT:
	case PACKET3_DISPATCH_INDIRECT:
	case PACKET3_MODE_CONTROL:
	case PACKET3_SET_PREDICATION:
	case PACKET3_COND_EXEC:
	case PACKET3_PRED_EXEC:
	case PACKET3_DRAW_INDIRECT:
	case PACKET3_DRAW_INDEX_INDIRECT:
	case PACKET3_INDEX_BASE:
	case PACKET3_DRAW_INDEX_2:
	case PACKET3_CONTEXT_CONTROL:
	case PACKET3_DRAW_INDEX_OFFSET:
	case PACKET3_INDEX_TYPE:
	case PACKET3_DRAW_INDEX:
	case PACKET3_DRAW_INDEX_AUTO:
	case PACKET3_DRAW_INDEX_IMMD:
	case PACKET3_NUM_INSTANCES:
	case PACKET3_DRAW_INDEX_MULTI_AUTO:
	case PACKET3_STRMOUT_BUFFER_UPDATE:
	case PACKET3_DRAW_INDEX_OFFSET_2:
	case PACKET3_DRAW_INDEX_MULTI_ELEMENT:
	case PACKET3_MPEG_INDEX:
	case PACKET3_WAIT_REG_MEM:
	case PACKET3_MEM_WRITE:
	case PACKET3_SURFACE_SYNC:
	case PACKET3_EVENT_WRITE:
	case PACKET3_EVENT_WRITE_EOP:
	case PACKET3_EVENT_WRITE_EOS:
	case PACKET3_SET_CONTEXT_REG:
	case PACKET3_SET_BOOL_CONST:
	case PACKET3_SET_LOOP_CONST:
	case PACKET3_SET_RESOURCE:
	case PACKET3_SET_SAMPLER:
	case PACKET3_SET_CTL_CONST:
	case PACKET3_SET_RESOURCE_OFFSET:
	case PACKET3_SET_CONTEXT_REG_INDIRECT:
	case PACKET3_SET_RESOURCE_INDIRECT:
	case CAYMAN_PACKET3_DEALLOC_STATE:
		break;
	case PACKET3_COND_WRITE:
		if (idx_value & 0x100) {
			reg = ib[idx + 5] * 4;
			if (!evergreen_vm_reg_valid(reg))
				return -EINVAL;
		}
		break;
	case PACKET3_COPY_DW:
		if (idx_value & 0x2) {
			reg = ib[idx + 3] * 4;
			if (!evergreen_vm_reg_valid(reg))
				return -EINVAL;
		}
		break;
	case PACKET3_SET_CONFIG_REG:
		start_reg = (idx_value << 2) + PACKET3_SET_CONFIG_REG_START;
		end_reg = 4 * pkt->count + start_reg - 4;
		if ((start_reg < PACKET3_SET_CONFIG_REG_START) ||
		    (start_reg >= PACKET3_SET_CONFIG_REG_END) ||
		    (end_reg >= PACKET3_SET_CONFIG_REG_END)) {
			DRM_ERROR("bad PACKET3_SET_CONFIG_REG\n");
			return -EINVAL;
		}
		for (i = 0; i < pkt->count; i++) {
			reg = start_reg + (4 * i);
			if (!evergreen_vm_reg_valid(reg))
				return -EINVAL;
		}
		break;
	case PACKET3_CP_DMA:
		command = ib[idx + 4];
		info = ib[idx + 1];
		if ((((info & 0x60000000) >> 29) != 0) || /* src = GDS or DATA */
		    (((info & 0x00300000) >> 20) != 0) || /* dst = GDS */
		    ((((info & 0x00300000) >> 20) == 0) &&
		     (command & PACKET3_CP_DMA_CMD_DAS)) || /* dst = register */
		    ((((info & 0x60000000) >> 29) == 0) &&
		     (command & PACKET3_CP_DMA_CMD_SAS))) { /* src = register */
			/* non mem to mem copies requires dw aligned count */
			if ((command & 0x1fffff) % 4) {
				DRM_ERROR("CP DMA command requires dw count alignment\n");
				return -EINVAL;
			}
		}
		if (command & PACKET3_CP_DMA_CMD_SAS) {
			/* src address space is register */
			if (((info & 0x60000000) >> 29) == 0) {
				start_reg = idx_value << 2;
				if (command & PACKET3_CP_DMA_CMD_SAIC) {
					reg = start_reg;
					if (!evergreen_vm_reg_valid(reg)) {
						DRM_ERROR("CP DMA Bad SRC register\n");
						return -EINVAL;
					}
				} else {
					for (i = 0; i < (command & 0x1fffff); i++) {
						reg = start_reg + (4 * i);
						if (!evergreen_vm_reg_valid(reg)) {
							DRM_ERROR("CP DMA Bad SRC register\n");
							return -EINVAL;
						}
					}
				}
			}
		}
		if (command & PACKET3_CP_DMA_CMD_DAS) {
			/* dst address space is register */
			if (((info & 0x00300000) >> 20) == 0) {
				start_reg = ib[idx + 2];
				if (command & PACKET3_CP_DMA_CMD_DAIC) {
					reg = start_reg;
					if (!evergreen_vm_reg_valid(reg)) {
						DRM_ERROR("CP DMA Bad DST register\n");
						return -EINVAL;
					}
				} else {
					for (i = 0; i < (command & 0x1fffff); i++) {
						reg = start_reg + (4 * i);
						if (!evergreen_vm_reg_valid(reg)) {
							DRM_ERROR("CP DMA Bad DST register\n");
							return -EINVAL;
						}
					}
				}
			}
		}
		break;
	default:
		return -EINVAL;
	}
	return 0;
}