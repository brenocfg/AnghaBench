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
struct TYPE_2__ {char* (* mangle_fundamental_type ) (scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ ARRAY_TYPE ; 
#define  BLOCK_POINTER_TYPE 147 
#define  BOOLEAN_TYPE 146 
#define  BOUND_TEMPLATE_TEMPLATE_PARM 145 
#define  COMPLEX_TYPE 144 
#define  ENUMERAL_TYPE 143 
#define  FUNCTION_TYPE 142 
#define  INTEGER_TYPE 141 
 int /*<<< orphan*/  MANGLE_TRACE_TREE (char*,scalar_t__) ; 
#define  METHOD_TYPE 140 
#define  POINTER_TYPE 139 
#define  REAL_TYPE 138 
#define  RECORD_TYPE 137 
#define  REFERENCE_TYPE 136 
#define  TEMPLATE_PARM_INDEX 135 
#define  TEMPLATE_TEMPLATE_PARM 134 
 int /*<<< orphan*/  TEMPLATE_TEMPLATE_PARM_TEMPLATE_INFO (scalar_t__) ; 
#define  TEMPLATE_TYPE_PARM 133 
 int /*<<< orphan*/  TI_ARGS (int /*<<< orphan*/ ) ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
#define  TYPENAME_TYPE 132 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_P (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEM_P (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_STUB_DECL (scalar_t__) ; 
#define  UNBOUND_CLASS_TEMPLATE 131 
#define  UNION_TYPE 130 
#define  VECTOR_TYPE 129 
#define  VOID_TYPE 128 
 int /*<<< orphan*/  add_substitution (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ find_substitution (scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 char* stub1 (scalar_t__) ; 
 TYPE_1__ targetm ; 
 scalar_t__ write_CV_qualifiers_for_type (scalar_t__) ; 
 int /*<<< orphan*/  write_array_type (scalar_t__) ; 
 int /*<<< orphan*/  write_builtin_type (scalar_t__) ; 
 int /*<<< orphan*/  write_char (char) ; 
 int /*<<< orphan*/  write_class_enum_type (scalar_t__) ; 
 int /*<<< orphan*/  write_function_type (scalar_t__) ; 
 int /*<<< orphan*/  write_nested_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pointer_to_member_type (scalar_t__) ; 
 int /*<<< orphan*/  write_string (char const*) ; 
 int /*<<< orphan*/  write_template_args (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_template_param (scalar_t__) ; 
 int /*<<< orphan*/  write_template_template_param (scalar_t__) ; 

__attribute__((used)) static void
write_type (tree type)
{
  /* This gets set to nonzero if TYPE turns out to be a (possibly
     CV-qualified) builtin type.  */
  int is_builtin_type = 0;

  MANGLE_TRACE_TREE ("type", type);

  if (type == error_mark_node)
    return;

  if (find_substitution (type))
    return;

  if (write_CV_qualifiers_for_type (type) > 0)
    /* If TYPE was CV-qualified, we just wrote the qualifiers; now
       mangle the unqualified type.  The recursive call is needed here
       since both the qualified and unqualified types are substitution
       candidates.  */
    write_type (TYPE_MAIN_VARIANT (type));
  else if (TREE_CODE (type) == ARRAY_TYPE)
    /* It is important not to use the TYPE_MAIN_VARIANT of TYPE here
       so that the cv-qualification of the element type is available
       in write_array_type.  */
    write_array_type (type);
  else
    {
      /* See through any typedefs.  */
      type = TYPE_MAIN_VARIANT (type);

      if (TYPE_PTRMEM_P (type))
	write_pointer_to_member_type (type);
      else switch (TREE_CODE (type))
	{
	case VOID_TYPE:
	case BOOLEAN_TYPE:
	case INTEGER_TYPE:  /* Includes wchar_t.  */
	case REAL_TYPE:
	{
	  /* Handle any target-specific fundamental types.  */
	  const char *target_mangling
	    = targetm.mangle_fundamental_type (type);

	  if (target_mangling)
	    {
	      write_string (target_mangling);
	      return;
	    }

	  /* If this is a typedef, TYPE may not be one of
	     the standard builtin type nodes, but an alias of one.  Use
	     TYPE_MAIN_VARIANT to get to the underlying builtin type.  */
	  write_builtin_type (TYPE_MAIN_VARIANT (type));
	  ++is_builtin_type;
	  break;
	}

	case COMPLEX_TYPE:
	  write_char ('C');
	  write_type (TREE_TYPE (type));
	  break;

	case FUNCTION_TYPE:
	case METHOD_TYPE:
	  write_function_type (type);
	  break;

	case UNION_TYPE:
	case RECORD_TYPE:
	case ENUMERAL_TYPE:
	  /* A pointer-to-member function is represented as a special
	     RECORD_TYPE, so check for this first.  */
	  if (TYPE_PTRMEMFUNC_P (type))
	    write_pointer_to_member_type (type);
	  else
	    write_class_enum_type (type);
	  break;

	case TYPENAME_TYPE:
	case UNBOUND_CLASS_TEMPLATE:
	  /* We handle TYPENAME_TYPEs and UNBOUND_CLASS_TEMPLATEs like
	     ordinary nested names.  */
	  write_nested_name (TYPE_STUB_DECL (type));
	  break;

	case POINTER_TYPE:
	  write_char ('P');
	  write_type (TREE_TYPE (type));
	  break;

	   /* APPLE LOCAL begin blocks 6040305 */
	 case BLOCK_POINTER_TYPE:
	   write_string ("U13block_pointer");
	   write_type (TREE_TYPE (type));
	   break;
	    /* APPLE LOCAL end blocks 6040305 */

	case REFERENCE_TYPE:
	  write_char ('R');
	  write_type (TREE_TYPE (type));
	  break;

	case TEMPLATE_TYPE_PARM:
	case TEMPLATE_PARM_INDEX:
	  write_template_param (type);
	  break;

	case TEMPLATE_TEMPLATE_PARM:
	  write_template_template_param (type);
	  break;

	case BOUND_TEMPLATE_TEMPLATE_PARM:
	  write_template_template_param (type);
	  write_template_args
	    (TI_ARGS (TEMPLATE_TEMPLATE_PARM_TEMPLATE_INFO (type)));
	  break;

	case VECTOR_TYPE:
	  write_string ("U8__vector");
	  write_type (TREE_TYPE (type));
	  break;

	default:
	  gcc_unreachable ();
	}
    }

  /* Types other than builtin types are substitution candidates.  */
  if (!is_builtin_type)
    add_substitution (type);
}