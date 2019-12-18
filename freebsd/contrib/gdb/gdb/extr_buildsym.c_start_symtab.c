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
struct context_stack {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int INITIAL_CONTEXT_STACK_SIZE ; 
 struct context_stack* context_stack ; 
 scalar_t__ context_stack_depth ; 
 int context_stack_size ; 
 int /*<<< orphan*/  cp_initialize_namespace () ; 
 int /*<<< orphan*/ * current_subfile ; 
 int /*<<< orphan*/ * file_symbols ; 
 int /*<<< orphan*/ * global_symbols ; 
 scalar_t__ have_line_numbers ; 
 char* last_source_file ; 
 int /*<<< orphan*/  last_source_start_addr ; 
 int /*<<< orphan*/  start_subfile (char*,char*) ; 
 int /*<<< orphan*/ * subfiles ; 
 scalar_t__ within_function ; 
 scalar_t__ xmalloc (int) ; 

void
start_symtab (char *name, char *dirname, CORE_ADDR start_addr)
{

  last_source_file = name;
  last_source_start_addr = start_addr;
  file_symbols = NULL;
  global_symbols = NULL;
  within_function = 0;
  have_line_numbers = 0;

  /* Context stack is initially empty.  Allocate first one with room
     for 10 levels; reuse it forever afterward.  */
  if (context_stack == NULL)
    {
      context_stack_size = INITIAL_CONTEXT_STACK_SIZE;
      context_stack = (struct context_stack *)
	xmalloc (context_stack_size * sizeof (struct context_stack));
    }
  context_stack_depth = 0;

  /* Set up support for C++ namespace support, in case we need it.  */

  cp_initialize_namespace ();

  /* Initialize the list of sub source files with one entry for this
     file (the top-level source file).  */

  subfiles = NULL;
  current_subfile = NULL;
  start_subfile (name, dirname);
}