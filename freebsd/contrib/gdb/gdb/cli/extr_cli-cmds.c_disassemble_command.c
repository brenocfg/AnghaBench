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
typedef  int /*<<< orphan*/  asection ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DISASSEM_WIN ; 
 scalar_t__ FUNCTION_START_OFFSET ; 
 int /*<<< orphan*/  deprecated_selected_frame ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ find_pc_partial_function (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_disassembly (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  get_frame_pc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_and_eval_address (char*) ; 
 int /*<<< orphan*/  print_address_numeric (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ tui_active ; 
 int /*<<< orphan*/  tui_get_low_disassembly_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_is_window_visible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_show_assembly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiout ; 

__attribute__((used)) static void
disassemble_command (char *arg, int from_tty)
{
  CORE_ADDR low, high;
  char *name;
  CORE_ADDR pc, pc_masked;
  char *space_index;
#if 0
  asection *section;
#endif

  name = NULL;
  if (!arg)
    {
      if (!deprecated_selected_frame)
	error ("No frame selected.\n");

      pc = get_frame_pc (deprecated_selected_frame);
      if (find_pc_partial_function (pc, &name, &low, &high) == 0)
	error ("No function contains program counter for selected frame.\n");
#if defined(TUI)
      /* NOTE: cagney/2003-02-13 The `tui_active' was previously
	 `tui_version'.  */
      if (tui_active)
	/* FIXME: cagney/2004-02-07: This should be an observer.  */
	low = tui_get_low_disassembly_address (low, pc);
#endif
      low += FUNCTION_START_OFFSET;
    }
  else if (!(space_index = (char *) strchr (arg, ' ')))
    {
      /* One argument.  */
      pc = parse_and_eval_address (arg);
      if (find_pc_partial_function (pc, &name, &low, &high) == 0)
	error ("No function contains specified address.\n");
#if defined(TUI)
      /* NOTE: cagney/2003-02-13 The `tui_active' was previously
	 `tui_version'.  */
      if (tui_active)
	/* FIXME: cagney/2004-02-07: This should be an observer.  */
	low = tui_get_low_disassembly_address (low, pc);
#endif
      low += FUNCTION_START_OFFSET;
    }
  else
    {
      /* Two arguments.  */
      *space_index = '\0';
      low = parse_and_eval_address (arg);
      high = parse_and_eval_address (space_index + 1);
    }

#if defined(TUI)
  if (!tui_is_window_visible (DISASSEM_WIN))
#endif
    {
      printf_filtered ("Dump of assembler code ");
      if (name != NULL)
	{
	  printf_filtered ("for function %s:\n", name);
	}
      else
	{
	  printf_filtered ("from ");
	  print_address_numeric (low, 1, gdb_stdout);
	  printf_filtered (" to ");
	  print_address_numeric (high, 1, gdb_stdout);
	  printf_filtered (":\n");
	}

      /* Dump the specified range.  */
      gdb_disassembly (uiout, 0, 0, 0, -1, low, high);

      printf_filtered ("End of assembler dump.\n");
      gdb_flush (gdb_stdout);
    }
#if defined(TUI)
  else
    {
      tui_show_assembly (low);
    }
#endif
}