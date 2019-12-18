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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
#define  CONST_DECL 134 
 int /*<<< orphan*/  DECL_CONSTRUCTOR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_CONV_FN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NONSTATIC_MEMBER_FUNCTION_P (int /*<<< orphan*/ ) ; 
#define  FIELD_DECL 133 
#define  FUNCTION_DECL 132 
#define  PARM_DECL 131 
#define  RECORD_TYPE 130 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  TYPE_DECL 129 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_FN_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_P (int /*<<< orphan*/ ) ; 
#define  VAR_DECL 128 
 int /*<<< orphan*/  pp_c_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_declaration_specifiers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_function_specifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_cxx_ptr_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_storage_class_specifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_whitespace (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_cxx_decl_specifier_seq (cxx_pretty_printer *pp, tree t)
{
  switch (TREE_CODE (t))
    {
    case VAR_DECL:
    case PARM_DECL:
    case CONST_DECL:
    case FIELD_DECL:
      pp_cxx_storage_class_specifier (pp, t);
      pp_cxx_decl_specifier_seq (pp, TREE_TYPE (t));
      break;

    case TYPE_DECL:
      pp_cxx_identifier (pp, "typedef");
      pp_cxx_decl_specifier_seq (pp, TREE_TYPE (t));
      break;

    case RECORD_TYPE:
      if (TYPE_PTRMEMFUNC_P (t))
	{
	  tree pfm = TYPE_PTRMEMFUNC_FN_TYPE (t);
	  pp_cxx_decl_specifier_seq (pp, TREE_TYPE (TREE_TYPE (pfm)));
	  pp_cxx_whitespace (pp);
	  pp_cxx_ptr_operator (pp, t);
	}
      break;

    case FUNCTION_DECL:
      /* Constructors don't have return types.  And conversion functions
	 do not have a type-specifier in their return types.  */
      if (DECL_CONSTRUCTOR_P (t) || DECL_CONV_FN_P (t))
	pp_cxx_function_specifier (pp, t);
      else if (DECL_NONSTATIC_MEMBER_FUNCTION_P (t))
	pp_cxx_decl_specifier_seq (pp, TREE_TYPE (TREE_TYPE (t)));
      else
	default:
      pp_c_declaration_specifiers (pp_c_base (pp), t);
      break;
    }
}