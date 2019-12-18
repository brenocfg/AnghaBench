#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct cgraph_node {int /*<<< orphan*/  decl; struct cgraph_node* next_nested; struct cgraph_node* nested; } ;
struct TYPE_2__ {char* (* decl_printable_name ) (int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_ASSEMBLER_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_SAVED_TREE (int /*<<< orphan*/ ) ; 
 char* IDENTIFIER_POINTER (int /*<<< orphan*/ ) ; 
 int TDF_RAW ; 
 int TDF_SLIM ; 
 int /*<<< orphan*/  TDI_generic ; 
 int /*<<< orphan*/  TDI_original ; 
 struct cgraph_node* cgraph_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dump_begin (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dump_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* dump_flag_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  gimplify_function_tree (int /*<<< orphan*/ ) ; 
 TYPE_1__ lang_hooks ; 
 int /*<<< orphan*/  print_c_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* stub1 (int /*<<< orphan*/ ,int) ; 
 char* stub2 (int /*<<< orphan*/ ,int) ; 

void
c_genericize (tree fndecl)
{
  FILE *dump_orig;
  int local_dump_flags;
  struct cgraph_node *cgn;

  /* Dump the C-specific tree IR.  */
  dump_orig = dump_begin (TDI_original, &local_dump_flags);
  if (dump_orig)
    {
      fprintf (dump_orig, "\n;; Function %s",
	       lang_hooks.decl_printable_name (fndecl, 2));
      fprintf (dump_orig, " (%s)\n",
	       IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (fndecl)));
      fprintf (dump_orig, ";; enabled by -%s\n", dump_flag_name (TDI_original));
      fprintf (dump_orig, "\n");

      if (local_dump_flags & TDF_RAW)
	dump_node (DECL_SAVED_TREE (fndecl),
		   TDF_SLIM | local_dump_flags, dump_orig);
      else
	print_c_tree (dump_orig, DECL_SAVED_TREE (fndecl));
      fprintf (dump_orig, "\n");

      dump_end (TDI_original, dump_orig);
    }

  /* Go ahead and gimplify for now.  */
  gimplify_function_tree (fndecl);

  /* Dump the genericized tree IR.  */
  dump_function (TDI_generic, fndecl);

  /* Genericize all nested functions now.  We do things in this order so
     that items like VLA sizes are expanded properly in the context of
     the correct function.  */
  cgn = cgraph_node (fndecl);
  for (cgn = cgn->nested; cgn ; cgn = cgn->next_nested)
    c_genericize (cgn->decl);
}