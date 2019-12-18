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
typedef  scalar_t__ tree ;
struct TYPE_2__ {scalar_t__ (* types_compatible_p ) (scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 int /*<<< orphan*/  ARRAY_REF ; 
 scalar_t__ ARRAY_TYPE ; 
 int /*<<< orphan*/  INDIRECT_REF ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  STRIP_USELESS_TYPE_CONVERSION (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_DOMAIN (scalar_t__) ; 
 scalar_t__ TYPE_MIN_VALUE (scalar_t__) ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build4 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_1__ lang_hooks ; 
 scalar_t__ size_zero_node ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__) ; 
 scalar_t__ stub2 (scalar_t__,scalar_t__) ; 
 scalar_t__ stub3 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static tree
fold_indirect_ref_rhs (tree t)
{
  tree type = TREE_TYPE (TREE_TYPE (t));
  tree sub = t;
  tree subtype;

  STRIP_USELESS_TYPE_CONVERSION (sub);
  subtype = TREE_TYPE (sub);
  if (!POINTER_TYPE_P (subtype))
    return NULL_TREE;

  if (TREE_CODE (sub) == ADDR_EXPR)
    {
      tree op = TREE_OPERAND (sub, 0);
      tree optype = TREE_TYPE (op);
      /* *&p => p */
      if (lang_hooks.types_compatible_p (type, optype))
        return op;
      /* *(foo *)&fooarray => fooarray[0] */
      else if (TREE_CODE (optype) == ARRAY_TYPE
	       && lang_hooks.types_compatible_p (type, TREE_TYPE (optype)))
       {
         tree type_domain = TYPE_DOMAIN (optype);
         tree min_val = size_zero_node;
         if (type_domain && TYPE_MIN_VALUE (type_domain))
           min_val = TYPE_MIN_VALUE (type_domain);
         return build4 (ARRAY_REF, type, op, min_val, NULL_TREE, NULL_TREE);
       }
    }

  /* *(foo *)fooarrptr => (*fooarrptr)[0] */
  if (TREE_CODE (TREE_TYPE (subtype)) == ARRAY_TYPE
      && lang_hooks.types_compatible_p (type, TREE_TYPE (TREE_TYPE (subtype))))
    {
      tree type_domain;
      tree min_val = size_zero_node;
      tree osub = sub;
      sub = fold_indirect_ref_rhs (sub);
      if (! sub)
	sub = build1 (INDIRECT_REF, TREE_TYPE (subtype), osub);
      type_domain = TYPE_DOMAIN (TREE_TYPE (sub));
      if (type_domain && TYPE_MIN_VALUE (type_domain))
        min_val = TYPE_MIN_VALUE (type_domain);
      return build4 (ARRAY_REF, type, sub, min_val, NULL_TREE, NULL_TREE);
    }

  return NULL_TREE;
}