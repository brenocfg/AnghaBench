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
 int /*<<< orphan*/  AGGREGATE_TYPE_P (scalar_t__) ; 
 scalar_t__ ARRAY_TYPE ; 
 int /*<<< orphan*/  COMPONENT_REF ; 
 scalar_t__ DECL_BIT_FIELD (scalar_t__) ; 
 int /*<<< orphan*/  DECL_FIELD_CONTEXT (scalar_t__) ; 
 scalar_t__ DECL_SIZE_UNIT (scalar_t__) ; 
 scalar_t__ FIELD_DECL ; 
 int /*<<< orphan*/  INDIRECT_REF ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ QUAL_UNION_TYPE ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 scalar_t__ UNION_TYPE ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build3 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ byte_position (scalar_t__) ; 
 scalar_t__ int_const_binop (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 TYPE_1__ lang_hooks ; 
 scalar_t__ maybe_fold_offset_to_array_ref (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__) ; 
 scalar_t__ stub2 (scalar_t__,scalar_t__) ; 
 int tree_int_cst_compare (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tree_int_cst_lt (scalar_t__,scalar_t__) ; 

__attribute__((used)) static tree
maybe_fold_offset_to_component_ref (tree record_type, tree base, tree offset,
				    tree orig_type, bool base_is_ptr)
{
  tree f, t, field_type, tail_array_field, field_offset;

  if (TREE_CODE (record_type) != RECORD_TYPE
      && TREE_CODE (record_type) != UNION_TYPE
      && TREE_CODE (record_type) != QUAL_UNION_TYPE)
    return NULL_TREE;

  /* Short-circuit silly cases.  */
  if (lang_hooks.types_compatible_p (record_type, orig_type))
    return NULL_TREE;

  tail_array_field = NULL_TREE;
  for (f = TYPE_FIELDS (record_type); f ; f = TREE_CHAIN (f))
    {
      int cmp;

      if (TREE_CODE (f) != FIELD_DECL)
	continue;
      if (DECL_BIT_FIELD (f))
	continue;

      field_offset = byte_position (f);
      if (TREE_CODE (field_offset) != INTEGER_CST)
	continue;

      /* ??? Java creates "interesting" fields for representing base classes.
	 They have no name, and have no context.  With no context, we get into
	 trouble with nonoverlapping_component_refs_p.  Skip them.  */
      if (!DECL_FIELD_CONTEXT (f))
	continue;

      /* The previous array field isn't at the end.  */
      tail_array_field = NULL_TREE;

      /* Check to see if this offset overlaps with the field.  */
      cmp = tree_int_cst_compare (field_offset, offset);
      if (cmp > 0)
	continue;

      field_type = TREE_TYPE (f);

      /* Here we exactly match the offset being checked.  If the types match,
	 then we can return that field.  */
      if (cmp == 0
	  && lang_hooks.types_compatible_p (orig_type, field_type))
	{
	  if (base_is_ptr)
	    base = build1 (INDIRECT_REF, record_type, base);
	  t = build3 (COMPONENT_REF, field_type, base, f, NULL_TREE);
	  return t;
	}
      
      /* Don't care about offsets into the middle of scalars.  */
      if (!AGGREGATE_TYPE_P (field_type))
	continue;

      /* Check for array at the end of the struct.  This is often
	 used as for flexible array members.  We should be able to
	 turn this into an array access anyway.  */
      if (TREE_CODE (field_type) == ARRAY_TYPE)
	tail_array_field = f;

      /* Check the end of the field against the offset.  */
      if (!DECL_SIZE_UNIT (f)
	  || TREE_CODE (DECL_SIZE_UNIT (f)) != INTEGER_CST)
	continue;
      t = int_const_binop (MINUS_EXPR, offset, field_offset, 1);
      if (!tree_int_cst_lt (t, DECL_SIZE_UNIT (f)))
	continue;

      /* If we matched, then set offset to the displacement into
	 this field.  */
      offset = t;
      goto found;
    }

  if (!tail_array_field)
    return NULL_TREE;

  f = tail_array_field;
  field_type = TREE_TYPE (f);
  offset = int_const_binop (MINUS_EXPR, offset, byte_position (f), 1);

 found:
  /* If we get here, we've got an aggregate field, and a possibly 
     nonzero offset into them.  Recurse and hope for a valid match.  */
  if (base_is_ptr)
    base = build1 (INDIRECT_REF, record_type, base);
  base = build3 (COMPONENT_REF, field_type, base, f, NULL_TREE);

  t = maybe_fold_offset_to_array_ref (base, offset, orig_type);
  if (t)
    return t;
  return maybe_fold_offset_to_component_ref (field_type, base, offset,
					     orig_type, false);
}