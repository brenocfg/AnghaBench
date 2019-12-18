#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* rtx ;
struct TYPE_4__ {int gr_used_mask; } ;
struct TYPE_3__ {int save_gr_used_mask; int n_iter; int /*<<< orphan*/ * iter_reg; scalar_t__ next_iter; void** prev_off; int /*<<< orphan*/ ** prev_insn; int /*<<< orphan*/ ** prev_addr; void** init_reg; int /*<<< orphan*/  init_after; } ;
typedef  void* HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  DImode ; 
 TYPE_2__ current_frame_info ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_last_insn () ; 
 int next_scratch_gr_reg () ; 
 TYPE_1__ spill_fill_data ; 

__attribute__((used)) static void
setup_spill_pointers (int n_spills, rtx init_reg, HOST_WIDE_INT cfa_off)
{
  int i;

  spill_fill_data.init_after = get_last_insn ();
  spill_fill_data.init_reg[0] = init_reg;
  spill_fill_data.init_reg[1] = init_reg;
  spill_fill_data.prev_addr[0] = NULL;
  spill_fill_data.prev_addr[1] = NULL;
  spill_fill_data.prev_insn[0] = NULL;
  spill_fill_data.prev_insn[1] = NULL;
  spill_fill_data.prev_off[0] = cfa_off;
  spill_fill_data.prev_off[1] = cfa_off;
  spill_fill_data.next_iter = 0;
  spill_fill_data.save_gr_used_mask = current_frame_info.gr_used_mask;

  spill_fill_data.n_iter = 1 + (n_spills > 2);
  for (i = 0; i < spill_fill_data.n_iter; ++i)
    {
      int regno = next_scratch_gr_reg ();
      spill_fill_data.iter_reg[i] = gen_rtx_REG (DImode, regno);
      current_frame_info.gr_used_mask |= 1 << regno;
    }
}