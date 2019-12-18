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
typedef  int /*<<< orphan*/  cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  cp_parser_block_declaration (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  declarator_obstack ; 
 int /*<<< orphan*/  finish_stmt () ; 
 void* obstack_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
cp_parser_declaration_statement (cp_parser* parser)
{
  void *p;

  /* Get the high-water mark for the DECLARATOR_OBSTACK.  */
  p = obstack_alloc (&declarator_obstack, 0);

 /* Parse the block-declaration.  */
  cp_parser_block_declaration (parser, /*statement_p=*/true);

  /* Free any declarators allocated.  */
  obstack_free (&declarator_obstack, p);

  /* Finish off the statement.  */
  finish_stmt ();
}