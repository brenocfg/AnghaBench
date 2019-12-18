#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct symbol {int dummy; } ;
typedef  struct symbol minimal_symbol ;
struct frame_info {int dummy; } ;
struct TYPE_5__ {struct TYPE_5__* next; struct symbol* symbol; } ;
struct TYPE_4__ {TYPE_2__* entries; } ;
typedef  TYPE_1__* SAVED_F77_COMMON_PTR ;
typedef  TYPE_2__* COMMON_ENTRY_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK_COMMON_NAME_LOCAL ; 
 scalar_t__ BLOCK_START (int /*<<< orphan*/ ) ; 
 char* DEPRECATED_SYMBOL_NAME (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_BLOCK_VALUE (struct symbol*) ; 
 scalar_t__ SYMBOL_VALUE_ADDRESS (struct symbol*) ; 
 struct frame_info* deprecated_selected_frame ; 
 int /*<<< orphan*/  error (char*) ; 
 TYPE_1__* find_common_for_function (char*,char*) ; 
 struct symbol* find_pc_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  get_frame_pc (struct frame_info*) ; 
 int /*<<< orphan*/  list_all_visible_commons (char*) ; 
 struct symbol* lookup_minimal_symbol_by_pc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_variable_value (struct symbol*,struct frame_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
info_common_command (char *comname, int from_tty)
{
  SAVED_F77_COMMON_PTR the_common;
  COMMON_ENTRY_PTR entry;
  struct frame_info *fi;
  char *funname = 0;
  struct symbol *func;

  /* We have been told to display the contents of F77 COMMON 
     block supposedly visible in this function.  Let us 
     first make sure that it is visible and if so, let 
     us display its contents */

  fi = deprecated_selected_frame;

  if (fi == NULL)
    error ("No frame selected");

  /* The following is generally ripped off from stack.c's routine 
     print_frame_info() */

  func = find_pc_function (get_frame_pc (fi));
  if (func)
    {
      /* In certain pathological cases, the symtabs give the wrong
         function (when we are in the first function in a file which
         is compiled without debugging symbols, the previous function
         is compiled with debugging symbols, and the "foo.o" symbol
         that is supposed to tell us where the file with debugging symbols
         ends has been truncated by ar because it is longer than 15
         characters).

         So look in the minimal symbol tables as well, and if it comes
         up with a larger address for the function use that instead.
         I don't think this can ever cause any problems; there shouldn't
         be any minimal symbols in the middle of a function.
         FIXME:  (Not necessarily true.  What about text labels) */

      struct minimal_symbol *msymbol = lookup_minimal_symbol_by_pc (get_frame_pc (fi));

      if (msymbol != NULL
	  && (SYMBOL_VALUE_ADDRESS (msymbol)
	      > BLOCK_START (SYMBOL_BLOCK_VALUE (func))))
	funname = DEPRECATED_SYMBOL_NAME (msymbol);
      else
	funname = DEPRECATED_SYMBOL_NAME (func);
    }
  else
    {
      struct minimal_symbol *msymbol =
      lookup_minimal_symbol_by_pc (get_frame_pc (fi));

      if (msymbol != NULL)
	funname = DEPRECATED_SYMBOL_NAME (msymbol);
    }

  /* If comname is NULL, we assume the user wishes to see the 
     which COMMON blocks are visible here and then return */

  if (comname == 0)
    {
      list_all_visible_commons (funname);
      return;
    }

  the_common = find_common_for_function (comname, funname);

  if (the_common)
    {
      if (strcmp (comname, BLANK_COMMON_NAME_LOCAL) == 0)
	printf_filtered ("Contents of blank COMMON block:\n");
      else
	printf_filtered ("Contents of F77 COMMON block '%s':\n", comname);

      printf_filtered ("\n");
      entry = the_common->entries;

      while (entry != NULL)
	{
	  printf_filtered ("%s = ", DEPRECATED_SYMBOL_NAME (entry->symbol));
	  print_variable_value (entry->symbol, fi, gdb_stdout);
	  printf_filtered ("\n");
	  entry = entry->next;
	}
    }
  else
    printf_filtered ("Cannot locate the common block %s in function '%s'\n",
		     comname, funname);
}