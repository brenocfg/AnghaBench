#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_57__   TYPE_3__ ;
typedef  struct TYPE_56__   TYPE_2__ ;
typedef  struct TYPE_55__   TYPE_1__ ;
typedef  struct TYPE_54__   TYPE_19__ ;

/* Type definitions */
typedef  TYPE_3__* tree ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_56__ {int /*<<< orphan*/  rtl; } ;
struct TYPE_57__ {TYPE_2__ decl_with_rtl; } ;
struct TYPE_55__ {TYPE_3__* (* type_for_mode ) (int /*<<< orphan*/ ,int) ;TYPE_3__* (* unsigned_type ) (TYPE_3__*) ;TYPE_3__* (* signed_type ) (TYPE_3__*) ;} ;
struct TYPE_54__ {TYPE_1__ types; } ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
#define  ASHIFT 143 
#define  ASHIFTRT 142 
#define  CONST 141 
#define  CONST_DOUBLE 140 
 int CONST_DOUBLE_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONST_DOUBLE_LOW (int /*<<< orphan*/ ) ; 
#define  CONST_INT 139 
#define  CONST_VECTOR 138 
 int /*<<< orphan*/  CONST_VECTOR_ELT (int /*<<< orphan*/ ,int) ; 
 int CONST_VECTOR_NUNITS (int /*<<< orphan*/ ) ; 
#define  DIV 137 
 int const GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_BITSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST_BITS_PER_WIDE_INT ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
#define  LSHIFTRT 136 
 int /*<<< orphan*/  LSHIFT_EXPR ; 
#define  MINUS 135 
 int /*<<< orphan*/  MINUS_EXPR ; 
#define  MULT 134 
 int /*<<< orphan*/  MULT_EXPR ; 
#define  NEG 133 
 int /*<<< orphan*/  NEGATE_EXPR ; 
 TYPE_3__* NULL_TREE ; 
#define  PLUS 132 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  POINTER_TYPE_P (TYPE_3__*) ; 
 int /*<<< orphan*/  REAL_TYPE ; 
 int /*<<< orphan*/  REAL_VALUE_FROM_CONST_DOUBLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSHIFT_EXPR ; 
#define  SIGN_EXTEND 131 
#define  SYMBOL_REF 130 
 TYPE_3__* SYMBOL_REF_DECL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CODE (TYPE_3__*) ; 
 TYPE_3__* TREE_TYPE (TYPE_3__*) ; 
 int /*<<< orphan*/  TRUNC_DIV_EXPR ; 
 int /*<<< orphan*/  TYPE_MODE (TYPE_3__*) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (TYPE_3__*) ; 
#define  UDIV 129 
 int /*<<< orphan*/  VAR_DECL ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
#define  ZERO_EXTEND 128 
 TYPE_3__* build2 (int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*,TYPE_3__*) ; 
 TYPE_3__* build_decl (int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*) ; 
 TYPE_3__* build_fold_addr_expr (TYPE_3__*) ; 
 TYPE_3__* build_int_cst_wide (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* build_real (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* build_vector (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  convert_memory_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* fold_build1 (int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*) ; 
 TYPE_3__* fold_build2 (int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*,TYPE_3__*) ; 
 TYPE_3__* fold_convert (TYPE_3__*,TYPE_3__*) ; 
 TYPE_19__ lang_hooks ; 
 TYPE_3__* stub1 (TYPE_3__*) ; 
 TYPE_3__* stub2 (TYPE_3__*) ; 
 TYPE_3__* stub3 (TYPE_3__*) ; 
 TYPE_3__* stub4 (TYPE_3__*) ; 
 TYPE_3__* stub5 (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* tree_cons (TYPE_3__*,TYPE_3__*,TYPE_3__*) ; 

tree
make_tree (tree type, rtx x)
{
  tree t;

  switch (GET_CODE (x))
    {
    case CONST_INT:
      {
	HOST_WIDE_INT hi = 0;

	if (INTVAL (x) < 0
	    && !(TYPE_UNSIGNED (type)
		 && (GET_MODE_BITSIZE (TYPE_MODE (type))
		     < HOST_BITS_PER_WIDE_INT)))
	  hi = -1;
      
	t = build_int_cst_wide (type, INTVAL (x), hi);
	
	return t;
      }
      
    case CONST_DOUBLE:
      if (GET_MODE (x) == VOIDmode)
	t = build_int_cst_wide (type,
				CONST_DOUBLE_LOW (x), CONST_DOUBLE_HIGH (x));
      else
	{
	  REAL_VALUE_TYPE d;

	  REAL_VALUE_FROM_CONST_DOUBLE (d, x);
	  t = build_real (type, d);
	}

      return t;

    case CONST_VECTOR:
      {
	int units = CONST_VECTOR_NUNITS (x);
	tree itype = TREE_TYPE (type);
	tree t = NULL_TREE;
	int i;


	/* Build a tree with vector elements.  */
	for (i = units - 1; i >= 0; --i)
	  {
	    rtx elt = CONST_VECTOR_ELT (x, i);
	    t = tree_cons (NULL_TREE, make_tree (itype, elt), t);
	  }

	return build_vector (type, t);
      }

    case PLUS:
      return fold_build2 (PLUS_EXPR, type, make_tree (type, XEXP (x, 0)),
			  make_tree (type, XEXP (x, 1)));

    case MINUS:
      return fold_build2 (MINUS_EXPR, type, make_tree (type, XEXP (x, 0)),
			  make_tree (type, XEXP (x, 1)));

    case NEG:
      return fold_build1 (NEGATE_EXPR, type, make_tree (type, XEXP (x, 0)));

    case MULT:
      return fold_build2 (MULT_EXPR, type, make_tree (type, XEXP (x, 0)),
			  make_tree (type, XEXP (x, 1)));

    case ASHIFT:
      return fold_build2 (LSHIFT_EXPR, type, make_tree (type, XEXP (x, 0)),
			  make_tree (type, XEXP (x, 1)));

    case LSHIFTRT:
      t = lang_hooks.types.unsigned_type (type);
      return fold_convert (type, build2 (RSHIFT_EXPR, t,
			    		 make_tree (t, XEXP (x, 0)),
				    	 make_tree (type, XEXP (x, 1))));

    case ASHIFTRT:
      t = lang_hooks.types.signed_type (type);
      return fold_convert (type, build2 (RSHIFT_EXPR, t,
					 make_tree (t, XEXP (x, 0)),
				    	 make_tree (type, XEXP (x, 1))));

    case DIV:
      if (TREE_CODE (type) != REAL_TYPE)
	t = lang_hooks.types.signed_type (type);
      else
	t = type;

      return fold_convert (type, build2 (TRUNC_DIV_EXPR, t,
				    	 make_tree (t, XEXP (x, 0)),
				    	 make_tree (t, XEXP (x, 1))));
    case UDIV:
      t = lang_hooks.types.unsigned_type (type);
      return fold_convert (type, build2 (TRUNC_DIV_EXPR, t,
				    	 make_tree (t, XEXP (x, 0)),
				    	 make_tree (t, XEXP (x, 1))));

    case SIGN_EXTEND:
    case ZERO_EXTEND:
      t = lang_hooks.types.type_for_mode (GET_MODE (XEXP (x, 0)),
					  GET_CODE (x) == ZERO_EXTEND);
      return fold_convert (type, make_tree (t, XEXP (x, 0)));

    case CONST:
      return make_tree (type, XEXP (x, 0));

    case SYMBOL_REF:
      t = SYMBOL_REF_DECL (x);
      if (t)
	return fold_convert (type, build_fold_addr_expr (t));
      /* else fall through.  */

    default:
      t = build_decl (VAR_DECL, NULL_TREE, type);

      /* If TYPE is a POINTER_TYPE, X might be Pmode with TYPE_MODE being
	 ptr_mode.  So convert.  */
      if (POINTER_TYPE_P (type))
	x = convert_memory_address (TYPE_MODE (type), x);

      /* Note that we do *not* use SET_DECL_RTL here, because we do not
	 want set_decl_rtl to go adjusting REG_ATTRS for this temporary.  */
      t->decl_with_rtl.rtl = x;

      return t;
    }
}