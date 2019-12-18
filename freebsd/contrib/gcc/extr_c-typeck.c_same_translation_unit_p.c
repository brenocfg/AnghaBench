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

/* Variables and functions */
 scalar_t__ BLOCK_SUPERCONTEXT (scalar_t__) ; 
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ TRANSLATION_UNIT_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int TREE_CODE_CLASS (scalar_t__) ; 
 scalar_t__ TYPE_CONTEXT (scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
#define  tcc_declaration 130 
#define  tcc_exceptional 129 
#define  tcc_type 128 

int
same_translation_unit_p (tree t1, tree t2)
{
  while (t1 && TREE_CODE (t1) != TRANSLATION_UNIT_DECL)
    switch (TREE_CODE_CLASS (TREE_CODE (t1)))
      {
      case tcc_declaration:
	t1 = DECL_CONTEXT (t1); break;
      case tcc_type:
	t1 = TYPE_CONTEXT (t1); break;
      case tcc_exceptional:
	t1 = BLOCK_SUPERCONTEXT (t1); break;  /* assume block */
      default: gcc_unreachable ();
      }

  while (t2 && TREE_CODE (t2) != TRANSLATION_UNIT_DECL)
    switch (TREE_CODE_CLASS (TREE_CODE (t2)))
      {
      case tcc_declaration:
	t2 = DECL_CONTEXT (t2); break;
      case tcc_type:
	t2 = TYPE_CONTEXT (t2); break;
      case tcc_exceptional:
	t2 = BLOCK_SUPERCONTEXT (t2); break;  /* assume block */
      default: gcc_unreachable ();
      }

  return t1 == t2;
}