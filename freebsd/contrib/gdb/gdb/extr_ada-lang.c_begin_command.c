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
struct minimal_symbol {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  ADA_MAIN_PROGRAM_SYMBOL_NAME ; 
 scalar_t__ SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 int begin_annotate_level ; 
 int /*<<< orphan*/  begin_cleanup ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  do_command (char*,char*,...) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  extract_string (scalar_t__,char*) ; 
 int /*<<< orphan*/  have_full_symbols () ; 
 int /*<<< orphan*/  have_partial_symbols () ; 
 struct minimal_symbol* lookup_minimal_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
begin_command (char *args, int from_tty)
{
  struct minimal_symbol *msym;
  CORE_ADDR main_program_name_addr;
  char main_program_name[1024];
  struct cleanup *old_chain = make_cleanup (begin_cleanup, NULL);
  begin_annotate_level = 2;

  /* Check that there is a program to debug */
  if (!have_full_symbols () && !have_partial_symbols ())
    error ("No symbol table is loaded.  Use the \"file\" command.");

  /* Check that we are debugging an Ada program */
  /*  if (ada_update_initial_language (language_unknown, NULL) != language_ada)
     error ("Cannot find the Ada initialization procedure.  Is this an Ada main program?");
   */
  /* FIXME: language_ada should be defined in defs.h */

  /* Get the address of the name of the main procedure */
  msym = lookup_minimal_symbol (ADA_MAIN_PROGRAM_SYMBOL_NAME, NULL, NULL);

  if (msym != NULL)
    {
      main_program_name_addr = SYMBOL_VALUE_ADDRESS (msym);
      if (main_program_name_addr == 0)
	error ("Invalid address for Ada main program name.");

      /* Read the name of the main procedure */
      extract_string (main_program_name_addr, main_program_name);

      /* Put a temporary breakpoint in the Ada main program and run */
      do_command ("tbreak ", main_program_name, 0);
      do_command ("run ", args, 0);
    }
  else
    {
      /* If we could not find the symbol containing the name of the
         main program, that means that the compiler that was used to build
         was not recent enough. In that case, we fallback to the previous
         mechanism, which is a little bit less reliable, but has proved to work
         in most cases. The only cases where it will fail is when the user
         has set some breakpoints which will be hit before the end of the
         begin command processing (eg in the initialization code).

         The begining of the main Ada subprogram is located by breaking
         on the adainit procedure. Since we know that the binder generates
         the call to this procedure exactly 2 calls before the call to the
         Ada main subprogram, it is then easy to put a breakpoint on this
         Ada main subprogram once we hit adainit.
       */
      do_command ("tbreak adainit", 0);
      do_command ("run ", args, 0);
      do_command ("up", 0);
      do_command ("tbreak +2", 0);
      do_command ("continue", 0);
      do_command ("step", 0);
    }

  do_cleanups (old_chain);
}