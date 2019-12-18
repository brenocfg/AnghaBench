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
struct symtab_and_line {int /*<<< orphan*/  pc; int /*<<< orphan*/  section; } ;
struct breakpoint {int /*<<< orphan*/  disposition; int /*<<< orphan*/  number; } ;
typedef  enum bptype { ____Placeholder_bptype } bptype ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  disp_donttouch ; 
 int /*<<< orphan*/  find_pc_overlay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_sal (struct symtab_and_line*) ; 
 struct breakpoint* set_raw_breakpoint (struct symtab_and_line,int) ; 

__attribute__((used)) static struct breakpoint *
create_internal_breakpoint (CORE_ADDR address, enum bptype type)
{
  static int internal_breakpoint_number = -1;
  struct symtab_and_line sal;
  struct breakpoint *b;

  init_sal (&sal);		/* initialize to zeroes */

  sal.pc = address;
  sal.section = find_pc_overlay (sal.pc);

  b = set_raw_breakpoint (sal, type);
  b->number = internal_breakpoint_number--;
  b->disposition = disp_donttouch;

  return b;
}