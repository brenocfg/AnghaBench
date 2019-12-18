#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* rtl; } ;
struct TYPE_6__ {TYPE_2__ il; } ;
struct TYPE_4__ {int /*<<< orphan*/  global_live_at_end; } ;

/* Variables and functions */
 TYPE_3__* ENTRY_BLOCK_PTR ; 
 scalar_t__ NUM_FIXED_BLOCKS ; 
 scalar_t__ REGNO_REG_SET_P (int /*<<< orphan*/ ,int) ; 
 int REG_N_SETS (int) ; 
 scalar_t__ n_basic_blocks ; 
 int /*<<< orphan*/  regs_live_at_setjmp ; 

int
regno_clobbered_at_setjmp (int regno)
{
  if (n_basic_blocks == NUM_FIXED_BLOCKS)
    return 0;

  return ((REG_N_SETS (regno) > 1
	   || REGNO_REG_SET_P (ENTRY_BLOCK_PTR->il.rtl->global_live_at_end,
	     		       regno))
	  && REGNO_REG_SET_P (regs_live_at_setjmp, regno));
}