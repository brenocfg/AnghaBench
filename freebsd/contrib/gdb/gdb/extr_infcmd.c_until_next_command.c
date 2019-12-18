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
struct symtab_and_line {int /*<<< orphan*/  end; } ;
struct symbol {int dummy; } ;
struct minimal_symbol {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_START (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STEP_OVER_ALL ; 
 int /*<<< orphan*/  SYMBOL_BLOCK_VALUE (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 int /*<<< orphan*/  TARGET_SIGNAL_DEFAULT ; 
 int /*<<< orphan*/  clear_proceed_status () ; 
 int /*<<< orphan*/  error (char*) ; 
 struct symbol* find_pc_function (int /*<<< orphan*/ ) ; 
 struct symtab_and_line find_pc_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct frame_info* get_current_frame () ; 
 int /*<<< orphan*/  get_frame_id (struct frame_info*) ; 
 struct minimal_symbol* lookup_minimal_symbol_by_pc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proceed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_pc () ; 
 int /*<<< orphan*/  read_sp () ; 
 int /*<<< orphan*/  step_frame_id ; 
 scalar_t__ step_multi ; 
 int /*<<< orphan*/  step_over_calls ; 
 int /*<<< orphan*/  step_range_end ; 
 int /*<<< orphan*/  step_range_start ; 
 int /*<<< orphan*/  step_sp ; 

__attribute__((used)) static void
until_next_command (int from_tty)
{
  struct frame_info *frame;
  CORE_ADDR pc;
  struct symbol *func;
  struct symtab_and_line sal;

  clear_proceed_status ();

  frame = get_current_frame ();

  /* Step until either exited from this function or greater
     than the current line (if in symbolic section) or pc (if
     not). */

  pc = read_pc ();
  func = find_pc_function (pc);

  if (!func)
    {
      struct minimal_symbol *msymbol = lookup_minimal_symbol_by_pc (pc);

      if (msymbol == NULL)
	error ("Execution is not within a known function.");

      step_range_start = SYMBOL_VALUE_ADDRESS (msymbol);
      step_range_end = pc;
    }
  else
    {
      sal = find_pc_line (pc, 0);

      step_range_start = BLOCK_START (SYMBOL_BLOCK_VALUE (func));
      step_range_end = sal.end;
    }

  step_over_calls = STEP_OVER_ALL;
  step_frame_id = get_frame_id (frame);
  step_sp = read_sp ();

  step_multi = 0;		/* Only one call to proceed */

  proceed ((CORE_ADDR) -1, TARGET_SIGNAL_DEFAULT, 1);
}