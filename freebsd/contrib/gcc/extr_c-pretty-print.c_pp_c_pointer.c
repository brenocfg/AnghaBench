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
typedef  int /*<<< orphan*/  tree ;
typedef  int pp_needs_newline ;
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
#define  BLOCK_POINTER_TYPE 131 
#define  DECL_EXPR 130 
 int /*<<< orphan*/  DECL_EXPR_DECL (int /*<<< orphan*/ ) ; 
#define  POINTER_TYPE 129 
#define  REFERENCE_TYPE 128 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int const TYPE_DECL ; 
 int /*<<< orphan*/  TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_ampersand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_caret (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_star (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_type_qualifier_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_declaration (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_c_pointer (c_pretty_printer *pp, tree t)
{
  if (!TYPE_P (t) && TREE_CODE (t) != TYPE_DECL)
    t = TREE_TYPE (t);
  switch (TREE_CODE (t))
    {
    case POINTER_TYPE:
      /* It is easier to handle C++ reference types here.  */
    case REFERENCE_TYPE:
      if (TREE_CODE (TREE_TYPE (t)) == POINTER_TYPE)
	pp_c_pointer (pp, TREE_TYPE (t));
      if (TREE_CODE (t) == POINTER_TYPE)
	pp_c_star (pp);
      else
	pp_c_ampersand (pp);
      pp_c_type_qualifier_list (pp, t);
      break;
    /* APPLE LOCAL begin blocks */
    case BLOCK_POINTER_TYPE:
      pp_c_caret (pp);
      pp_c_type_qualifier_list (pp, t);
      break;
    /* APPLE LOCAL end blocks */

      /* ??? This node is now in GENERIC and so shouldn't be here.  But
	 we'll fix that later.  */
    case DECL_EXPR:
      pp_declaration (pp, DECL_EXPR_DECL (t));
      pp_needs_newline (pp) = true;
      break;

    default:
      pp_unsupported_tree (pp, t);
    }
}