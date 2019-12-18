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

/* Variables and functions */
 int /*<<< orphan*/  DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 int FIELD_DECL ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
#define  PTRMEM_CST 128 
 int /*<<< orphan*/  PTRMEM_CST_MEMBER (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_CLASS_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_nop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_ptrmemfunc1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  byte_position (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_ptrmemfunc_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_anon_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
cplus_expand_constant (tree cst)
{
  switch (TREE_CODE (cst))
    {
    case PTRMEM_CST:
      {
	tree type = TREE_TYPE (cst);
	tree member;

	/* Find the member.  */
	member = PTRMEM_CST_MEMBER (cst);

	if (TREE_CODE (member) == FIELD_DECL)
	  {
	    /* Find the offset for the field.  */
	    cst = byte_position (member);
	    while (!same_type_p (DECL_CONTEXT (member),
				 TYPE_PTRMEM_CLASS_TYPE (type)))
	      {
		/* The MEMBER must have been nestled within an
		   anonymous aggregate contained in TYPE.  Find the
		   anonymous aggregate.  */
		member = lookup_anon_field (TYPE_PTRMEM_CLASS_TYPE (type),
					    DECL_CONTEXT (member));
		cst = size_binop (PLUS_EXPR, cst, byte_position (member));
	      }
	    cst = fold (build_nop (type, cst));
	  }
	else
	  {
	    tree delta;
	    tree pfn;

	    expand_ptrmemfunc_cst (cst, &delta, &pfn);
	    cst = build_ptrmemfunc1 (type, delta, pfn);
	  }
      }
      break;

    default:
      /* There's nothing to do.  */
      break;
    }

  return cst;
}