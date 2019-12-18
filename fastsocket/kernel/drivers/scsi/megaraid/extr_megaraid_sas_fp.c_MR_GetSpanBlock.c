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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ noElements; struct MR_QUAD_ELEMENT* quad; } ;
struct MR_SPAN_BLOCK_INFO {TYPE_1__ block_span_info; } ;
struct MR_QUAD_ELEMENT {scalar_t__ diff; scalar_t__ logStart; scalar_t__ logEnd; scalar_t__ offsetInSpan; } ;
struct MR_LD_RAID {scalar_t__ spanDepth; scalar_t__ stripeShift; } ;
struct MR_FW_RAID_MAP_ALL {int dummy; } ;

/* Variables and functions */
 struct MR_LD_RAID* MR_LdRaidGet (scalar_t__,struct MR_FW_RAID_MAP_ALL*) ; 
 struct MR_SPAN_BLOCK_INFO* MR_LdSpanInfoGet (scalar_t__,struct MR_FW_RAID_MAP_ALL*) ; 
 scalar_t__ SPAN_INVALID ; 
 scalar_t__ mega_div64_32 (scalar_t__,scalar_t__) ; 
 scalar_t__ mega_mod64 (scalar_t__,scalar_t__) ; 

u32 MR_GetSpanBlock(u32 ld, u64 row, u64 *span_blk,
		    struct MR_FW_RAID_MAP_ALL *map)
{
	struct MR_SPAN_BLOCK_INFO *pSpanBlock = MR_LdSpanInfoGet(ld, map);
	struct MR_QUAD_ELEMENT    *quad;
	struct MR_LD_RAID         *raid = MR_LdRaidGet(ld, map);
	u32                span, j;

	for (span = 0; span < raid->spanDepth; span++, pSpanBlock++) {

		for (j = 0; j < pSpanBlock->block_span_info.noElements; j++) {
			quad = &pSpanBlock->block_span_info.quad[j];

			if (quad->diff == 0)
				return SPAN_INVALID;
			if (quad->logStart <= row  &&  row <= quad->logEnd  &&
			    (mega_mod64(row-quad->logStart, quad->diff)) == 0) {
				if (span_blk != NULL) {
					u64  blk, debugBlk;
					blk =
						mega_div64_32(
							(row-quad->logStart),
							quad->diff);
					debugBlk = blk;

					blk = (blk + quad->offsetInSpan) <<
						raid->stripeShift;
					*span_blk = blk;
				}
				return span;
			}
		}
	}
	return SPAN_INVALID;
}