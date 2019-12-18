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
typedef  enum tree_node_structure_enum { ____Placeholder_tree_node_structure_enum } tree_node_structure_enum ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
#define  BLOCK 164 
#define  COMPLEX_CST 163 
#define  CONSTRUCTOR 162 
#define  CONST_DECL 161 
#define  ERROR_MARK 160 
#define  FIELD_DECL 159 
#define  FUNCTION_DECL 158 
#define  IDENTIFIER_NODE 157 
#define  INTEGER_CST 156 
#define  LABEL_DECL 155 
#define  NAME_MEMORY_TAG 154 
#define  OMP_CLAUSE 153 
#define  PARM_DECL 152 
#define  PHI_NODE 151 
#define  PLACEHOLDER_EXPR 150 
#define  REAL_CST 149 
#define  RESULT_DECL 148 
#define  SSA_NAME 147 
#define  STATEMENT_LIST 146 
#define  STRING_CST 145 
#define  STRUCT_FIELD_TAG 144 
#define  SYMBOL_MEMORY_TAG 143 
#define  TREE_BINFO 142 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_CODE_CLASS (int) ; 
#define  TREE_LIST 141 
#define  TREE_VEC 140 
 int TS_BINFO ; 
 int TS_BLOCK ; 
 int TS_COMMON ; 
 int TS_COMPLEX ; 
 int TS_CONSTRUCTOR ; 
 int TS_CONST_DECL ; 
 int TS_DECL_NON_COMMON ; 
 int TS_EXP ; 
 int TS_FIELD_DECL ; 
 int TS_FUNCTION_DECL ; 
 int TS_IDENTIFIER ; 
 int TS_INT_CST ; 
 int TS_LABEL_DECL ; 
 int TS_LIST ; 
 int TS_MEMORY_TAG ; 
 int TS_OMP_CLAUSE ; 
 int TS_PARM_DECL ; 
 int TS_PHI_NODE ; 
 int TS_REAL_CST ; 
 int TS_RESULT_DECL ; 
 int TS_SSA_NAME ; 
 int TS_STATEMENT_LIST ; 
 int TS_STRING ; 
 int TS_TYPE ; 
 int TS_TYPE_DECL ; 
 int TS_VALUE_HANDLE ; 
 int TS_VAR_DECL ; 
 int TS_VEC ; 
 int TS_VECTOR ; 
#define  TYPE_DECL 139 
#define  VALUE_HANDLE 138 
#define  VAR_DECL 137 
#define  VECTOR_CST 136 
 int /*<<< orphan*/  gcc_unreachable () ; 
#define  tcc_binary 135 
#define  tcc_comparison 134 
#define  tcc_declaration 133 
#define  tcc_expression 132 
#define  tcc_reference 131 
#define  tcc_statement 130 
#define  tcc_type 129 
#define  tcc_unary 128 

enum tree_node_structure_enum
tree_node_structure (tree t)
{
  enum tree_code code = TREE_CODE (t);

  switch (TREE_CODE_CLASS (code))
    {      
    case tcc_declaration:
      {
	switch (code)
	  {
	  case FIELD_DECL:
	    return TS_FIELD_DECL;
	  case PARM_DECL:
	    return TS_PARM_DECL;
	  case VAR_DECL:
	    return TS_VAR_DECL;
	  case LABEL_DECL:
	    return TS_LABEL_DECL;
	  case RESULT_DECL:
	    return TS_RESULT_DECL;
	  case CONST_DECL:
	    return TS_CONST_DECL;
	  case TYPE_DECL:
	    return TS_TYPE_DECL;
	  case FUNCTION_DECL:
	    return TS_FUNCTION_DECL;
	  case SYMBOL_MEMORY_TAG:
	  case NAME_MEMORY_TAG:
	  case STRUCT_FIELD_TAG:
	    return TS_MEMORY_TAG;
	  default:
	    return TS_DECL_NON_COMMON;
	  }
      }
    case tcc_type:
      return TS_TYPE;
    case tcc_reference:
    case tcc_comparison:
    case tcc_unary:
    case tcc_binary:
    case tcc_expression:
    case tcc_statement:
      return TS_EXP;
    default:  /* tcc_constant and tcc_exceptional */
      break;
    }
  switch (code)
    {
      /* tcc_constant cases.  */
    case INTEGER_CST:		return TS_INT_CST;
    case REAL_CST:		return TS_REAL_CST;
    case COMPLEX_CST:		return TS_COMPLEX;
    case VECTOR_CST:		return TS_VECTOR;
    case STRING_CST:		return TS_STRING;
      /* tcc_exceptional cases.  */
    case ERROR_MARK:		return TS_COMMON;
    case IDENTIFIER_NODE:	return TS_IDENTIFIER;
    case TREE_LIST:		return TS_LIST;
    case TREE_VEC:		return TS_VEC;
    case PHI_NODE:		return TS_PHI_NODE;
    case SSA_NAME:		return TS_SSA_NAME;
    case PLACEHOLDER_EXPR:	return TS_COMMON;
    case STATEMENT_LIST:	return TS_STATEMENT_LIST;
    case BLOCK:			return TS_BLOCK;
    case CONSTRUCTOR:		return TS_CONSTRUCTOR;
    case TREE_BINFO:		return TS_BINFO;
    case VALUE_HANDLE:		return TS_VALUE_HANDLE;
    case OMP_CLAUSE:		return TS_OMP_CLAUSE;

    default:
      gcc_unreachable ();
    }
}