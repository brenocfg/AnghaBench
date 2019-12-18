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
struct arg_lookup {int dummy; } ;

/* Variables and functions */
#define  ARRAY_TYPE 147 
#define  BLOCK_POINTER_TYPE 146 
#define  BOOLEAN_TYPE 145 
#define  BOUND_TEMPLATE_TEMPLATE_PARM 144 
#define  COMPLEX_TYPE 143 
#define  ENUMERAL_TYPE 142 
#define  ERROR_MARK 141 
#define  FUNCTION_TYPE 140 
#define  INTEGER_TYPE 139 
#define  LANG_TYPE 138 
#define  METHOD_TYPE 137 
#define  POINTER_TYPE 136 
#define  REAL_TYPE 135 
#define  RECORD_TYPE 134 
#define  REFERENCE_TYPE 133 
#define  TEMPLATE_TYPE_PARM 132 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  TYPENAME_TYPE 131 
 int /*<<< orphan*/  TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_FN_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_CLASS_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PTRMEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_POINTED_TO_TYPE (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 130 
#define  VECTOR_TYPE 129 
#define  VOID_TYPE 128 
 int /*<<< orphan*/  arg_assoc_args (struct arg_lookup*,int /*<<< orphan*/ ) ; 
 int arg_assoc_class (struct arg_lookup*,int /*<<< orphan*/ ) ; 
 int arg_assoc_namespace (struct arg_lookup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decl_namespace_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  unknown_type_node ; 

__attribute__((used)) static bool
arg_assoc_type (struct arg_lookup *k, tree type)
{
  /* As we do not get the type of non-type dependent expressions
     right, we can end up with such things without a type.  */
  if (!type)
    return false;

  if (TYPE_PTRMEM_P (type))
    {
      /* Pointer to member: associate class type and value type.  */
      if (arg_assoc_type (k, TYPE_PTRMEM_CLASS_TYPE (type)))
	return true;
      return arg_assoc_type (k, TYPE_PTRMEM_POINTED_TO_TYPE (type));
    }
  else switch (TREE_CODE (type))
    {
    case ERROR_MARK:
      return false;
    case VOID_TYPE:
    case INTEGER_TYPE:
    case REAL_TYPE:
    case COMPLEX_TYPE:
    case VECTOR_TYPE:
    case BOOLEAN_TYPE:
      return false;
    case RECORD_TYPE:
      if (TYPE_PTRMEMFUNC_P (type))
	return arg_assoc_type (k, TYPE_PTRMEMFUNC_FN_TYPE (type));
      return arg_assoc_class (k, type);
    case POINTER_TYPE:
      /* APPLE LOCAL blocks 6040305 */
    case BLOCK_POINTER_TYPE:
    case REFERENCE_TYPE:
    case ARRAY_TYPE:
      return arg_assoc_type (k, TREE_TYPE (type));
    case UNION_TYPE:
    case ENUMERAL_TYPE:
      return arg_assoc_namespace (k, decl_namespace_context (type));
    case METHOD_TYPE:
      /* The basetype is referenced in the first arg type, so just
	 fall through.  */
    case FUNCTION_TYPE:
      /* Associate the parameter types.  */
      if (arg_assoc_args (k, TYPE_ARG_TYPES (type)))
	return true;
      /* Associate the return type.  */
      return arg_assoc_type (k, TREE_TYPE (type));
    case TEMPLATE_TYPE_PARM:
    case BOUND_TEMPLATE_TEMPLATE_PARM:
      return false;
    case TYPENAME_TYPE:
      return false;
    case LANG_TYPE:
      gcc_assert (type == unknown_type_node);
      return false;
    default:
      gcc_unreachable ();
    }
  return false;
}