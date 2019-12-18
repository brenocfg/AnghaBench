#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct megasas_instance {TYPE_5__* pdev; struct fusion_context* ctrl_context; } ;
struct fusion_context {TYPE_6__* log_to_span; } ;
struct MR_QUAD_ELEMENT {scalar_t__ logStart; scalar_t__ logEnd; int /*<<< orphan*/  diff; } ;
struct MR_LD_RAID {size_t spanDepth; } ;
struct TYPE_11__ {TYPE_3__* ldSpanMap; } ;
struct MR_FW_RAID_MAP_ALL {TYPE_4__ raidMap; } ;
struct TYPE_14__ {scalar_t__ span_row_data_width; scalar_t__ data_row_end; scalar_t__ data_row_start; scalar_t__* strip_offset; scalar_t__ data_strip_start; } ;
struct TYPE_13__ {TYPE_7__* span_set; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {TYPE_2__* spanBlock; } ;
struct TYPE_8__ {size_t noElements; struct MR_QUAD_ELEMENT* quad; } ;
struct TYPE_9__ {TYPE_1__ block_span_info; } ;
typedef  TYPE_6__* PLD_SPAN_INFO ;
typedef  TYPE_7__ LD_SPAN_SET ;

/* Variables and functions */
 size_t MAX_QUAD_DEPTH ; 
 struct MR_LD_RAID* MR_LdRaidGet (size_t,struct MR_FW_RAID_MAP_ALL*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t,unsigned long) ; 
 scalar_t__ mega_div64_32 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mega_mod64 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 get_strip_from_row(struct megasas_instance *instance,
		u32 ld, u64 row, struct MR_FW_RAID_MAP_ALL *map)
{
	struct fusion_context *fusion = instance->ctrl_context;
	struct MR_LD_RAID         *raid = MR_LdRaidGet(ld, map);
	LD_SPAN_SET *span_set;
	struct MR_QUAD_ELEMENT    *quad;
	PLD_SPAN_INFO ldSpanInfo = fusion->log_to_span;
	u32    span, info;
	u64  strip;

	for (info = 0; info < MAX_QUAD_DEPTH; info++) {
		span_set = &(ldSpanInfo[ld].span_set[info]);

		if (span_set->span_row_data_width == 0)
			break;
		if (row > span_set->data_row_end)
			continue;

		for (span = 0; span < raid->spanDepth; span++)
			if (map->raidMap.ldSpanMap[ld].spanBlock[span].
				block_span_info.noElements >= info+1) {
				quad = &map->raidMap.ldSpanMap[ld].
					spanBlock[span].block_span_info.quad[info];
				if (quad->logStart <= row  &&
					row <= quad->logEnd  &&
					mega_mod64((row - quad->logStart),
					quad->diff) == 0) {
					strip = mega_div64_32
						(((row - span_set->data_row_start)
							- quad->logStart),
							quad->diff);
					strip *= span_set->span_row_data_width;
					strip += span_set->data_strip_start;
					strip += span_set->strip_offset[span];
					return strip;
				}
			}
	}
	dev_err(&instance->pdev->dev, "get_strip_from_row"
		"returns invalid strip for ld=%x, row=%lx\n",
		ld, (long unsigned int)row);
	return -1;
}