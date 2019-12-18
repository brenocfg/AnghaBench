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
struct bb_info {int /*<<< orphan*/  avloc; int /*<<< orphan*/  killed; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  void* basic_block ;

/* Variables and functions */
 struct bb_info* BB_INFO (void*) ; 
 scalar_t__ CLOBBER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_clear_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mark_reg_change (rtx reg, rtx setter, void *data)
{
  int regno;
  basic_block bb = data;
  struct bb_info *bb_info = BB_INFO (bb);

  if (GET_CODE (reg) == SUBREG)
    reg = SUBREG_REG (reg);

  if (!REG_P (reg))
    return;

  regno = REGNO (reg);
  bitmap_set_bit (bb_info->killed, regno);
  
  if (GET_CODE (setter) != CLOBBER)
    bitmap_set_bit (bb_info->avloc, regno);
  else
    bitmap_clear_bit (bb_info->avloc, regno);
}