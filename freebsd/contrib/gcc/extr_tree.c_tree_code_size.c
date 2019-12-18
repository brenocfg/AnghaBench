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
struct tree_vector {int dummy; } ;
struct tree_var_decl {int dummy; } ;
struct tree_value_handle {int dummy; } ;
struct tree_type_decl {int dummy; } ;
struct tree_type {int dummy; } ;
struct tree_struct_field_tag {int dummy; } ;
struct tree_statement_list {int dummy; } ;
struct tree_ssa_name {int dummy; } ;
struct tree_result_decl {int dummy; } ;
struct tree_real_cst {int dummy; } ;
struct tree_parm_decl {int dummy; } ;
struct tree_memory_tag {int dummy; } ;
struct tree_list {int dummy; } ;
struct tree_label_decl {int dummy; } ;
struct tree_int_cst {int dummy; } ;
struct tree_function_decl {int dummy; } ;
struct tree_field_decl {int dummy; } ;
struct tree_exp {int dummy; } ;
struct tree_decl_non_common {int dummy; } ;
struct tree_constructor {int dummy; } ;
struct tree_const_decl {int dummy; } ;
struct tree_complex {int dummy; } ;
struct tree_common {int dummy; } ;
struct tree_block {int dummy; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_2__ {size_t (* tree_size ) (int) ;size_t identifier_size; } ;

/* Variables and functions */
#define  BLOCK 165 
#define  COMPLEX_CST 164 
#define  CONSTRUCTOR 163 
#define  CONST_DECL 162 
#define  ERROR_MARK 161 
#define  FIELD_DECL 160 
#define  FUNCTION_DECL 159 
#define  IDENTIFIER_NODE 158 
#define  INTEGER_CST 157 
#define  LABEL_DECL 156 
#define  NAME_MEMORY_TAG 155 
#define  OMP_CLAUSE 154 
#define  PARM_DECL 153 
#define  PHI_NODE 152 
#define  PLACEHOLDER_EXPR 151 
#define  REAL_CST 150 
#define  RESULT_DECL 149 
#define  SSA_NAME 148 
#define  STATEMENT_LIST 147 
#define  STRING_CST 146 
#define  STRUCT_FIELD_TAG 145 
#define  SYMBOL_MEMORY_TAG 144 
 int TREE_CODE_CLASS (int) ; 
 int /*<<< orphan*/  TREE_CODE_LENGTH (int) ; 
#define  TREE_LIST 143 
#define  TREE_VEC 142 
#define  TYPE_DECL 141 
#define  VALUE_HANDLE 140 
#define  VAR_DECL 139 
#define  VECTOR_CST 138 
 int /*<<< orphan*/  gcc_unreachable () ; 
 TYPE_1__ lang_hooks ; 
 size_t stub1 (int) ; 
 size_t stub2 (int) ; 
#define  tcc_binary 137 
#define  tcc_comparison 136 
#define  tcc_constant 135 
#define  tcc_declaration 134 
#define  tcc_exceptional 133 
#define  tcc_expression 132 
#define  tcc_reference 131 
#define  tcc_statement 130 
#define  tcc_type 129 
#define  tcc_unary 128 

size_t
tree_code_size (enum tree_code code)
{
  switch (TREE_CODE_CLASS (code))
    {
    case tcc_declaration:  /* A decl node */
      {
	switch (code)
	  {
	  case FIELD_DECL:
	    return sizeof (struct tree_field_decl);
	  case PARM_DECL:
	    return sizeof (struct tree_parm_decl);
	  case VAR_DECL:
	    return sizeof (struct tree_var_decl);
	  case LABEL_DECL:
	    return sizeof (struct tree_label_decl);
	  case RESULT_DECL:
	    return sizeof (struct tree_result_decl);
	  case CONST_DECL:
	    return sizeof (struct tree_const_decl);
	  case TYPE_DECL:
	    return sizeof (struct tree_type_decl);
	  case FUNCTION_DECL:
	    return sizeof (struct tree_function_decl);
	  case NAME_MEMORY_TAG:
	  case SYMBOL_MEMORY_TAG:
	    return sizeof (struct tree_memory_tag);
	  case STRUCT_FIELD_TAG:
	    return sizeof (struct tree_struct_field_tag);
	  default:
	    return sizeof (struct tree_decl_non_common);
	  }
      }

    case tcc_type:  /* a type node */
      return sizeof (struct tree_type);

    case tcc_reference:   /* a reference */
    case tcc_expression:  /* an expression */
    case tcc_statement:   /* an expression with side effects */
    case tcc_comparison:  /* a comparison expression */
    case tcc_unary:       /* a unary arithmetic expression */
    case tcc_binary:      /* a binary arithmetic expression */
      return (sizeof (struct tree_exp)
	      + (TREE_CODE_LENGTH (code) - 1) * sizeof (char *));

    case tcc_constant:  /* a constant */
      switch (code)
	{
	case INTEGER_CST:	return sizeof (struct tree_int_cst);
	case REAL_CST:		return sizeof (struct tree_real_cst);
	case COMPLEX_CST:	return sizeof (struct tree_complex);
	case VECTOR_CST:	return sizeof (struct tree_vector);
	case STRING_CST:	gcc_unreachable ();
	default:
	  return lang_hooks.tree_size (code);
	}

    case tcc_exceptional:  /* something random, like an identifier.  */
      switch (code)
	{
	case IDENTIFIER_NODE:	return lang_hooks.identifier_size;
	case TREE_LIST:		return sizeof (struct tree_list);

	case ERROR_MARK:
	case PLACEHOLDER_EXPR:	return sizeof (struct tree_common);

	case TREE_VEC:
	case OMP_CLAUSE:
	case PHI_NODE:		gcc_unreachable ();

	case SSA_NAME:		return sizeof (struct tree_ssa_name);

	case STATEMENT_LIST:	return sizeof (struct tree_statement_list);
	case BLOCK:		return sizeof (struct tree_block);
	case VALUE_HANDLE:	return sizeof (struct tree_value_handle);
	case CONSTRUCTOR:	return sizeof (struct tree_constructor);

	default:
	  return lang_hooks.tree_size (code);
	}

    default:
      gcc_unreachable ();
    }
}