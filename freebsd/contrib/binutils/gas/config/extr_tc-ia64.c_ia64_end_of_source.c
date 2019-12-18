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
struct TYPE_3__ {scalar_t__ hint; } ;
struct TYPE_4__ {TYPE_1__ mem_offset; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_set_private_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia64_flush_insns () ; 
 int /*<<< orphan*/  insn_group_break (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ md ; 
 int /*<<< orphan*/  stdoutput ; 

void
ia64_end_of_source ()
{
  /* terminate insn group upon reaching end of file:  */
  insn_group_break (1, 0, 0);

  /* emits slots we haven't written yet:  */
  ia64_flush_insns ();

  bfd_set_private_flags (stdoutput, md.flags);

  md.mem_offset.hint = 0;
}