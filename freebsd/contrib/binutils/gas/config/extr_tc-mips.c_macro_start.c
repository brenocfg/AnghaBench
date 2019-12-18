#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* insn_mo; } ;
struct TYPE_7__ {int delay_slot_p; int /*<<< orphan*/  sizes; } ;
struct TYPE_6__ {scalar_t__ noreorder; } ;
struct TYPE_5__ {int pinfo; } ;

/* Variables and functions */
 int INSN_COND_BRANCH_DELAY ; 
 int INSN_COND_BRANCH_LIKELY ; 
 int INSN_UNCOND_BRANCH_DELAY ; 
 TYPE_4__* history ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ mips_macro_warning ; 
 TYPE_2__ mips_opts ; 

__attribute__((used)) static void
macro_start (void)
{
  memset (&mips_macro_warning.sizes, 0, sizeof (mips_macro_warning.sizes));
  mips_macro_warning.delay_slot_p = (mips_opts.noreorder
				     && (history[0].insn_mo->pinfo
					 & (INSN_UNCOND_BRANCH_DELAY
					    | INSN_COND_BRANCH_DELAY
					    | INSN_COND_BRANCH_LIKELY)) != 0);
}