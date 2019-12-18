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
 int /*<<< orphan*/  ADDR_EXPR ; 
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ CLASSTYPE_DESTRUCTORS (scalar_t__) ; 
 scalar_t__ CLASSTYPE_DESTRUCTOR_NONTRIVIAL_BECAUSE_OF_BASE (scalar_t__) ; 
 scalar_t__ CLASSTYPE_HAS_NONTRIVIAL_DESTRUCTOR_BODY (scalar_t__) ; 
 scalar_t__ CLASSTYPE_VBASECLASSES (scalar_t__) ; 
 int LOOKUP_DESTRUCTOR ; 
 int LOOKUP_NONVIRTUAL ; 
 int LOOKUP_NORMAL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_PRIVATE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int TYPE_HAS_NONTRIVIAL_DESTRUCTOR (scalar_t__) ; 
 scalar_t__ build_delete (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ build_unary_op (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxx_mark_addressable (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ flag_expensive_optimizations ; 
 int /*<<< orphan*/  sfk_complete_destructor ; 

tree
cxx_maybe_build_cleanup (tree decl)
{
  tree type = TREE_TYPE (decl);

  /* APPLE LOCAL begin omit calls to empty destructors 5559195 */
  tree dtor = NULL_TREE;
  bool build_cleanup = false;

  if (TREE_CODE (type) == RECORD_TYPE)
    dtor = CLASSTYPE_DESTRUCTORS (type);

  if (type != error_mark_node)
    {
      if (TREE_CODE (type) == RECORD_TYPE)
	/* For RECORD_TYPEs, we can refer to more precise flags than
	   TYPE_HAS_NONTRIVIAL_DESTRUCTOR. */
	build_cleanup = (dtor && TREE_PRIVATE (dtor))
	  || CLASSTYPE_HAS_NONTRIVIAL_DESTRUCTOR_BODY (type)
	  || CLASSTYPE_DESTRUCTOR_NONTRIVIAL_BECAUSE_OF_BASE (type);
      else
	build_cleanup = TYPE_HAS_NONTRIVIAL_DESTRUCTOR (type);
    }

  if (build_cleanup)
    {
  /* APPLE LOCAL end omit calls to empty destructors 5559195 */
      int flags = LOOKUP_NORMAL|LOOKUP_DESTRUCTOR;
      tree rval;
      bool has_vbases = (TREE_CODE (type) == RECORD_TYPE
			 && CLASSTYPE_VBASECLASSES (type));
      if (TREE_CODE (type) == ARRAY_TYPE)
	rval = decl;
      else
	{
	  cxx_mark_addressable (decl);
	  rval = build_unary_op (ADDR_EXPR, decl, 0);
	}

      /* Optimize for space over speed here.  */
      if (!has_vbases || flag_expensive_optimizations)
	flags |= LOOKUP_NONVIRTUAL;

      rval = build_delete (TREE_TYPE (rval), rval,
			   sfk_complete_destructor, flags, 0);

      return rval;
    }
  return NULL_TREE;
}