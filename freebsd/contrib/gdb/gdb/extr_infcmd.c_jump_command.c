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
struct symtabs_and_lines {int nelts; struct symtab_and_line* sals; } ;
struct symtab_and_line {scalar_t__ symtab; scalar_t__ pc; int /*<<< orphan*/  line; } ;
struct symbol {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_NO_INFERIOR ; 
 int /*<<< orphan*/  SYMBOL_BFD_SECTION (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_PRINT_NAME (struct symbol*) ; 
 int /*<<< orphan*/  TARGET_SIGNAL_0 ; 
 int /*<<< orphan*/  async_disable_stdin () ; 
 int /*<<< orphan*/  clear_proceed_status () ; 
 struct symtabs_and_lines decode_line_spec_1 (char*,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error_no_arg (char*) ; 
 scalar_t__ event_loop_p ; 
 struct symbol* find_pc_function (scalar_t__) ; 
 int /*<<< orphan*/  fixup_symbol_section (struct symbol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  get_current_frame () ; 
 struct symbol* get_frame_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_address_numeric (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int /*<<< orphan*/  proceed (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query (char*,...) ; 
 int /*<<< orphan*/  resolve_sal_pc (struct symtab_and_line*) ; 
 int /*<<< orphan*/  section_is_mapped (int /*<<< orphan*/ ) ; 
 scalar_t__ section_is_overlay (int /*<<< orphan*/ ) ; 
 int strip_bg_char (char**) ; 
 scalar_t__ target_can_async_p () ; 
 int /*<<< orphan*/  xfree (struct symtab_and_line*) ; 

__attribute__((used)) static void
jump_command (char *arg, int from_tty)
{
  CORE_ADDR addr;
  struct symtabs_and_lines sals;
  struct symtab_and_line sal;
  struct symbol *fn;
  struct symbol *sfn;
  int async_exec = 0;

  ERROR_NO_INFERIOR;

  /* Find out whether we must run in the background. */
  if (arg != NULL)
    async_exec = strip_bg_char (&arg);

  /* If we must run in the background, but the target can't do it,
     error out. */
  if (event_loop_p && async_exec && !target_can_async_p ())
    error ("Asynchronous execution not supported on this target.");

  /* If we are not asked to run in the bg, then prepare to run in the
     foreground, synchronously. */
  if (event_loop_p && !async_exec && target_can_async_p ())
    {
      /* Simulate synchronous execution */
      async_disable_stdin ();
    }

  if (!arg)
    error_no_arg ("starting address");

  sals = decode_line_spec_1 (arg, 1);
  if (sals.nelts != 1)
    {
      error ("Unreasonable jump request");
    }

  sal = sals.sals[0];
  xfree (sals.sals);

  if (sal.symtab == 0 && sal.pc == 0)
    error ("No source file has been specified.");

  resolve_sal_pc (&sal);	/* May error out */

  /* See if we are trying to jump to another function. */
  fn = get_frame_function (get_current_frame ());
  sfn = find_pc_function (sal.pc);
  if (fn != NULL && sfn != fn)
    {
      if (!query ("Line %d is not in `%s'.  Jump anyway? ", sal.line,
		  SYMBOL_PRINT_NAME (fn)))
	{
	  error ("Not confirmed.");
	  /* NOTREACHED */
	}
    }

  if (sfn != NULL)
    {
      fixup_symbol_section (sfn, 0);
      if (section_is_overlay (SYMBOL_BFD_SECTION (sfn)) &&
	  !section_is_mapped (SYMBOL_BFD_SECTION (sfn)))
	{
	  if (!query ("WARNING!!!  Destination is in unmapped overlay!  Jump anyway? "))
	    {
	      error ("Not confirmed.");
	      /* NOTREACHED */
	    }
	}
    }

  addr = sal.pc;

  if (from_tty)
    {
      printf_filtered ("Continuing at ");
      print_address_numeric (addr, 1, gdb_stdout);
      printf_filtered (".\n");
    }

  clear_proceed_status ();
  proceed (addr, TARGET_SIGNAL_0, 0);
}