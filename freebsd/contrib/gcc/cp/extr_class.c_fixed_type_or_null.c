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
typedef  void* tree ;
typedef  int /*<<< orphan*/  htab_t ;

/* Variables and functions */
#define  ADDR_EXPR 141 
 int const ARRAY_TYPE ; 
#define  CALL_EXPR 140 
#define  COMPONENT_REF 139 
#define  CONVERT_EXPR 138 
 int /*<<< orphan*/  DECL_CONSTRUCTOR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_DESTRUCTOR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_FIELD_IS_BASE (void*) ; 
 void* DECL_INITIAL (void*) ; 
 int /*<<< orphan*/  DECL_LANG_SPECIFIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_P (void*) ; 
#define  FIELD_DECL 137 
#define  INDIRECT_REF 136 
 int /*<<< orphan*/  INSERT ; 
 int const INTEGER_CST ; 
 int /*<<< orphan*/  IS_AGGR_TYPE (void*) ; 
#define  MINUS_EXPR 135 
#define  NOP_EXPR 134 
 void* NULL_TREE ; 
#define  PARM_DECL 133 
#define  PLUS_EXPR 132 
 int /*<<< orphan*/  POINTER_TYPE_P (void*) ; 
 int const REFERENCE_TYPE ; 
#define  RESULT_DECL 131 
#define  SAVE_EXPR 130 
#define  TARGET_EXPR 129 
 int const TREE_CODE (void*) ; 
 int /*<<< orphan*/  TREE_HAS_CONSTRUCTOR (void*) ; 
 void* TREE_OPERAND (void*,int) ; 
 void* TREE_TYPE (void*) ; 
#define  VAR_DECL 128 
 void* current_class_ptr ; 
 int /*<<< orphan*/  current_function_decl ; 
 void* get_base_address (void*) ; 
 int /*<<< orphan*/  htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab_eq_pointer ; 
 int /*<<< orphan*/  htab_find (int /*<<< orphan*/ ,void*) ; 
 void** htab_find_slot (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_pointer ; 
 int /*<<< orphan*/  htab_remove_elt (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static tree
fixed_type_or_null (tree instance, int* nonnull, int* cdtorp)
{
  switch (TREE_CODE (instance))
    {
    case INDIRECT_REF:
      if (POINTER_TYPE_P (TREE_TYPE (instance)))
	return NULL_TREE;
      else
	return fixed_type_or_null (TREE_OPERAND (instance, 0),
				   nonnull, cdtorp);

    case CALL_EXPR:
      /* This is a call to a constructor, hence it's never zero.  */
      if (TREE_HAS_CONSTRUCTOR (instance))
	{
	  if (nonnull)
	    *nonnull = 1;
	  return TREE_TYPE (instance);
	}
      return NULL_TREE;

    case SAVE_EXPR:
      /* This is a call to a constructor, hence it's never zero.  */
      if (TREE_HAS_CONSTRUCTOR (instance))
	{
	  if (nonnull)
	    *nonnull = 1;
	  return TREE_TYPE (instance);
	}
      return fixed_type_or_null (TREE_OPERAND (instance, 0), nonnull, cdtorp);

    case PLUS_EXPR:
    case MINUS_EXPR:
      if (TREE_CODE (TREE_OPERAND (instance, 0)) == ADDR_EXPR)
	return fixed_type_or_null (TREE_OPERAND (instance, 0), nonnull, cdtorp);
      if (TREE_CODE (TREE_OPERAND (instance, 1)) == INTEGER_CST)
	/* Propagate nonnull.  */
	return fixed_type_or_null (TREE_OPERAND (instance, 0), nonnull, cdtorp);
      return NULL_TREE;

    case NOP_EXPR:
    case CONVERT_EXPR:
      return fixed_type_or_null (TREE_OPERAND (instance, 0), nonnull, cdtorp);

    case ADDR_EXPR:
      instance = TREE_OPERAND (instance, 0);
      if (nonnull)
	{
	  /* Just because we see an ADDR_EXPR doesn't mean we're dealing
	     with a real object -- given &p->f, p can still be null.  */
	  tree t = get_base_address (instance);
	  /* ??? Probably should check DECL_WEAK here.  */
	  if (t && DECL_P (t))
	    *nonnull = 1;
	}
      return fixed_type_or_null (instance, nonnull, cdtorp);

    case COMPONENT_REF:
      /* If this component is really a base class reference, then the field
	 itself isn't definitive.  */
      if (DECL_FIELD_IS_BASE (TREE_OPERAND (instance, 1)))
	return fixed_type_or_null (TREE_OPERAND (instance, 0), nonnull, cdtorp);
      return fixed_type_or_null (TREE_OPERAND (instance, 1), nonnull, cdtorp);

    case VAR_DECL:
    case FIELD_DECL:
      if (TREE_CODE (TREE_TYPE (instance)) == ARRAY_TYPE
	  && IS_AGGR_TYPE (TREE_TYPE (TREE_TYPE (instance))))
	{
	  if (nonnull)
	    *nonnull = 1;
	  return TREE_TYPE (TREE_TYPE (instance));
	}
      /* fall through...  */
    case TARGET_EXPR:
    case PARM_DECL:
    case RESULT_DECL:
      if (IS_AGGR_TYPE (TREE_TYPE (instance)))
	{
	  if (nonnull)
	    *nonnull = 1;
	  return TREE_TYPE (instance);
	}
      else if (instance == current_class_ptr)
	{
	  if (nonnull)
	    *nonnull = 1;

	  /* if we're in a ctor or dtor, we know our type.  */
	  if (DECL_LANG_SPECIFIC (current_function_decl)
	      && (DECL_CONSTRUCTOR_P (current_function_decl)
		  || DECL_DESTRUCTOR_P (current_function_decl)))
	    {
	      if (cdtorp)
		*cdtorp = 1;
	      return TREE_TYPE (TREE_TYPE (instance));
	    }
	}
      else if (TREE_CODE (TREE_TYPE (instance)) == REFERENCE_TYPE)
	{
	  /* We only need one hash table because it is always left empty.  */
	  static htab_t ht;
	  if (!ht)
	    ht = htab_create (37, 
			      htab_hash_pointer,
			      htab_eq_pointer,
			      /*htab_del=*/NULL);

	  /* Reference variables should be references to objects.  */
	  if (nonnull)
	    *nonnull = 1;

	  /* Enter the INSTANCE in a table to prevent recursion; a
	     variable's initializer may refer to the variable
	     itself.  */
	  if (TREE_CODE (instance) == VAR_DECL
	      && DECL_INITIAL (instance)
	      && !htab_find (ht, instance))
	    {
	      tree type;
	      void **slot;

	      slot = htab_find_slot (ht, instance, INSERT);
	      *slot = instance;
	      type = fixed_type_or_null (DECL_INITIAL (instance),
					 nonnull, cdtorp);
	      htab_remove_elt (ht, instance);

	      return type;
	    }
	}
      return NULL_TREE;

    default:
      return NULL_TREE;
    }
}