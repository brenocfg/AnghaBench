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
struct mtd_part {scalar_t__ offset; } ;
struct erase_info {scalar_t__ fail_addr; int /*<<< orphan*/  (* callback ) (struct erase_info*) ;int /*<<< orphan*/  addr; TYPE_1__* mtd; } ;
struct TYPE_2__ {scalar_t__ erase; } ;

/* Variables and functions */
 scalar_t__ MTD_FAIL_ADDR_UNKNOWN ; 
 struct mtd_part* PART (TYPE_1__*) ; 
 scalar_t__ part_erase ; 
 int /*<<< orphan*/  stub1 (struct erase_info*) ; 

void mtd_erase_callback(struct erase_info *instr)
{
	if (instr->mtd->erase == part_erase) {
		struct mtd_part *part = PART(instr->mtd);

		if (instr->fail_addr != MTD_FAIL_ADDR_UNKNOWN)
			instr->fail_addr -= part->offset;
		instr->addr -= part->offset;
	}
	if (instr->callback)
		instr->callback(instr);
}