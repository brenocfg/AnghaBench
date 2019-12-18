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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ BLOCK_VARS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DECL_INITIAL (scalar_t__) ; 
 int TDF_SLIM ; 
 int /*<<< orphan*/  TDI_tu ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TV_SYMOUT ; 
 scalar_t__ all_translation_units ; 
 int /*<<< orphan*/  build_cdtor (char,scalar_t__) ; 
 int /*<<< orphan*/  c_write_global_declarations_1 (scalar_t__) ; 
 int /*<<< orphan*/  c_write_global_declarations_2 (scalar_t__) ; 
 int /*<<< orphan*/  cgraph_optimize () ; 
 scalar_t__ cpp_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_scope ; 
 int /*<<< orphan*/ * dump_begin (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dump_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_node (scalar_t__,int,int /*<<< orphan*/ *) ; 
 scalar_t__ errorcount ; 
 int /*<<< orphan*/ * ext_block ; 
 scalar_t__ external_scope ; 
 scalar_t__ flag_syntax_only ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  parse_in ; 
 scalar_t__ pch_file ; 
 int /*<<< orphan*/ * pop_scope () ; 
 scalar_t__ sorrycount ; 
 scalar_t__ static_ctors ; 
 scalar_t__ static_dtors ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

void
c_write_global_declarations (void)
{
  tree t;

  /* We don't want to do this if generating a PCH.  */
  if (pch_file)
    return;

  /* Don't waste time on further processing if -fsyntax-only or we've
     encountered errors.  */
  if (flag_syntax_only || errorcount || sorrycount || cpp_errors (parse_in))
    return;

  /* Close the external scope.  */
  ext_block = pop_scope ();
  external_scope = 0;
  gcc_assert (!current_scope);

  if (ext_block)
    {
      tree tmp = BLOCK_VARS (ext_block);
      int flags;
      FILE * stream = dump_begin (TDI_tu, &flags);
      if (stream && tmp)
	{
	  dump_node (tmp, flags & ~TDF_SLIM, stream);
	  dump_end (TDI_tu, stream);
	}
    }

  /* Process all file scopes in this compilation, and the external_scope,
     through wrapup_global_declarations and check_global_declarations.  */
  for (t = all_translation_units; t; t = TREE_CHAIN (t))
    c_write_global_declarations_1 (BLOCK_VARS (DECL_INITIAL (t)));
  c_write_global_declarations_1 (BLOCK_VARS (ext_block));

  /* Generate functions to call static constructors and destructors
     for targets that do not support .ctors/.dtors sections.  These
     functions have magic names which are detected by collect2.  */
  build_cdtor ('I', static_ctors); static_ctors = 0;
  build_cdtor ('D', static_dtors); static_dtors = 0;

  /* We're done parsing; proceed to optimize and emit assembly.
     FIXME: shouldn't be the front end's responsibility to call this.  */
  cgraph_optimize ();

  /* After cgraph has had a chance to emit everything that's going to
     be emitted, output debug information for globals.  */
  if (errorcount == 0 && sorrycount == 0)
    {
      timevar_push (TV_SYMOUT);
      for (t = all_translation_units; t; t = TREE_CHAIN (t))
	c_write_global_declarations_2 (BLOCK_VARS (DECL_INITIAL (t)));
      c_write_global_declarations_2 (BLOCK_VARS (ext_block));
      timevar_pop (TV_SYMOUT);
    }

  ext_block = NULL;
}