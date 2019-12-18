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
struct z_candidate {int dummy; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
#define  ADDR_EXPR 145 
#define  COMPONENT_REF 144 
#define  COMPOUND_EXPR 143 
#define  COND_EXPR 142 
 scalar_t__ CP_TYPE_CONST_P (scalar_t__) ; 
 scalar_t__ ENUMERAL_TYPE ; 
#define  EQ_EXPR 141 
#define  GE_EXPR 140 
#define  GT_EXPR 139 
 scalar_t__ INTEGRAL_TYPE_P (scalar_t__) ; 
 scalar_t__ IS_AGGR_TYPE (scalar_t__) ; 
#define  LE_EXPR 138 
#define  LT_EXPR 137 
#define  MODIFY_EXPR 136 
#define  NE_EXPR 135 
 int NOP_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
#define  POSTDECREMENT_EXPR 134 
#define  POSTINCREMENT_EXPR 133 
#define  PREDECREMENT_EXPR 132 
#define  PREINCREMENT_EXPR 131 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
#define  TRUTH_ANDIF_EXPR 130 
#define  TRUTH_NOT_EXPR 129 
#define  TRUTH_ORIF_EXPR 128 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 int /*<<< orphan*/  add_builtin_candidate (struct z_candidate**,int,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ boolean_type_node ; 
 int /*<<< orphan*/  build_builtin_candidate (struct z_candidate**,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ build_reference_type (scalar_t__) ; 
 scalar_t__ lookup_conversions (scalar_t__) ; 
 scalar_t__ lvalue_type (scalar_t__) ; 
 scalar_t__ non_reference (scalar_t__) ; 
 scalar_t__ real_lvalue_p (scalar_t__) ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ type_decays_to (scalar_t__) ; 
 scalar_t__ type_promotes_to (scalar_t__) ; 
 int /*<<< orphan*/  value_member (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
add_builtin_candidates (struct z_candidate **candidates, enum tree_code code,
			enum tree_code code2, tree fnname, tree *args,
			int flags)
{
  int ref1, i;
  int enum_p = 0;
  tree type, argtypes[3];
  /* TYPES[i] is the set of possible builtin-operator parameter types
     we will consider for the Ith argument.  These are represented as
     a TREE_LIST; the TREE_VALUE of each node is the potential
     parameter type.  */
  tree types[2];

  for (i = 0; i < 3; ++i)
    {
      if (args[i])
	argtypes[i]  = lvalue_type (args[i]);
      else
	argtypes[i] = NULL_TREE;
    }

  switch (code)
    {
/* 4 For every pair T, VQ), where T is an arithmetic or  enumeration  type,
     and  VQ  is  either  volatile or empty, there exist candidate operator
     functions of the form
		 VQ T&   operator++(VQ T&);  */

    case POSTINCREMENT_EXPR:
    case PREINCREMENT_EXPR:
    case POSTDECREMENT_EXPR:
    case PREDECREMENT_EXPR:
    case MODIFY_EXPR:
      ref1 = 1;
      break;

/* 24There also exist candidate operator functions of the form
	     bool    operator!(bool);
	     bool    operator&&(bool, bool);
	     bool    operator||(bool, bool);  */

    case TRUTH_NOT_EXPR:
      build_builtin_candidate
	(candidates, fnname, boolean_type_node,
	 NULL_TREE, args, argtypes, flags);
      return;

    case TRUTH_ORIF_EXPR:
    case TRUTH_ANDIF_EXPR:
      build_builtin_candidate
	(candidates, fnname, boolean_type_node,
	 boolean_type_node, args, argtypes, flags);
      return;

    case ADDR_EXPR:
    case COMPOUND_EXPR:
    case COMPONENT_REF:
      return;

    case COND_EXPR:
    case EQ_EXPR:
    case NE_EXPR:
    case LT_EXPR:
    case LE_EXPR:
    case GT_EXPR:
    case GE_EXPR:
      enum_p = 1;
      /* Fall through.  */

    default:
      ref1 = 0;
    }

  types[0] = types[1] = NULL_TREE;

  for (i = 0; i < 2; ++i)
    {
      if (! args[i])
	;
      else if (IS_AGGR_TYPE (argtypes[i]))
	{
	  tree convs;

	  if (i == 0 && code == MODIFY_EXPR && code2 == NOP_EXPR)
	    return;

	  convs = lookup_conversions (argtypes[i]);

	  if (code == COND_EXPR)
	    {
	      if (real_lvalue_p (args[i]))
		types[i] = tree_cons
		  (NULL_TREE, build_reference_type (argtypes[i]), types[i]);

	      types[i] = tree_cons
		(NULL_TREE, TYPE_MAIN_VARIANT (argtypes[i]), types[i]);
	    }

	  else if (! convs)
	    return;

	  for (; convs; convs = TREE_CHAIN (convs))
	    {
	      type = TREE_TYPE (TREE_TYPE (OVL_CURRENT (TREE_VALUE (convs))));

	      if (i == 0 && ref1
		  && (TREE_CODE (type) != REFERENCE_TYPE
		      || CP_TYPE_CONST_P (TREE_TYPE (type))))
		continue;

	      if (code == COND_EXPR && TREE_CODE (type) == REFERENCE_TYPE)
		types[i] = tree_cons (NULL_TREE, type, types[i]);

	      type = non_reference (type);
	      if (i != 0 || ! ref1)
		{
		  type = TYPE_MAIN_VARIANT (type_decays_to (type));
		  if (enum_p && TREE_CODE (type) == ENUMERAL_TYPE)
		    types[i] = tree_cons (NULL_TREE, type, types[i]);
		  if (INTEGRAL_TYPE_P (type))
		    type = type_promotes_to (type);
		}

	      if (! value_member (type, types[i]))
		types[i] = tree_cons (NULL_TREE, type, types[i]);
	    }
	}
      else
	{
	  if (code == COND_EXPR && real_lvalue_p (args[i]))
	    types[i] = tree_cons
	      (NULL_TREE, build_reference_type (argtypes[i]), types[i]);
	  type = non_reference (argtypes[i]);
	  if (i != 0 || ! ref1)
	    {
	      type = TYPE_MAIN_VARIANT (type_decays_to (type));
	      if (enum_p && TREE_CODE (type) == ENUMERAL_TYPE)
		types[i] = tree_cons (NULL_TREE, type, types[i]);
	      if (INTEGRAL_TYPE_P (type))
		type = type_promotes_to (type);
	    }
	  types[i] = tree_cons (NULL_TREE, type, types[i]);
	}
    }

  /* Run through the possible parameter types of both arguments,
     creating candidates with those parameter types.  */
  for (; types[0]; types[0] = TREE_CHAIN (types[0]))
    {
      if (types[1])
	for (type = types[1]; type; type = TREE_CHAIN (type))
	  add_builtin_candidate
	    (candidates, code, code2, fnname, TREE_VALUE (types[0]),
	     TREE_VALUE (type), args, argtypes, flags);
      else
	add_builtin_candidate
	  (candidates, code, code2, fnname, TREE_VALUE (types[0]),
	   NULL_TREE, args, argtypes, flags);
    }
}