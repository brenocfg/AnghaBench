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
struct reg_avail_info {int last_set; int first_set; TYPE_1__* last_bb; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {size_t index; } ;

/* Variables and functions */
 int INSN_CUID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* current_bb ; 
 struct reg_avail_info* reg_avail_info ; 
 int /*<<< orphan*/ * reg_set_in_block ; 

__attribute__((used)) static void
record_last_reg_set_info (rtx insn, int regno)
{
  struct reg_avail_info *info = &reg_avail_info[regno];
  int cuid = INSN_CUID (insn);

  info->last_set = cuid;
  if (info->last_bb != current_bb)
    {
      info->last_bb = current_bb;
      info->first_set = cuid;
      SET_BIT (reg_set_in_block[current_bb->index], regno);
    }
}