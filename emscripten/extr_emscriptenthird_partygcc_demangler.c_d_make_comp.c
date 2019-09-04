#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct demangle_component* right; struct demangle_component* left; } ;
struct TYPE_4__ {TYPE_1__ s_binary; } ;
struct demangle_component {int type; TYPE_2__ u; } ;
struct d_info {int dummy; } ;
typedef  enum demangle_component_type { ____Placeholder_demangle_component_type } demangle_component_type ;

/* Variables and functions */
#define  DEMANGLE_COMPONENT_ARGLIST 170 
#define  DEMANGLE_COMPONENT_ARRAY_TYPE 169 
#define  DEMANGLE_COMPONENT_BINARY 168 
#define  DEMANGLE_COMPONENT_BINARY_ARGS 167 
#define  DEMANGLE_COMPONENT_CAST 166 
#define  DEMANGLE_COMPONENT_COMPLEX 165 
#define  DEMANGLE_COMPONENT_CONST 164 
#define  DEMANGLE_COMPONENT_CONSTRUCTION_VTABLE 163 
#define  DEMANGLE_COMPONENT_CONST_THIS 162 
#define  DEMANGLE_COMPONENT_COVARIANT_THUNK 161 
#define  DEMANGLE_COMPONENT_FUNCTION_TYPE 160 
#define  DEMANGLE_COMPONENT_GUARD 159 
#define  DEMANGLE_COMPONENT_HIDDEN_ALIAS 158 
#define  DEMANGLE_COMPONENT_IMAGINARY 157 
#define  DEMANGLE_COMPONENT_JAVA_CLASS 156 
#define  DEMANGLE_COMPONENT_LITERAL 155 
#define  DEMANGLE_COMPONENT_LITERAL_NEG 154 
#define  DEMANGLE_COMPONENT_LOCAL_NAME 153 
#define  DEMANGLE_COMPONENT_POINTER 152 
#define  DEMANGLE_COMPONENT_PTRMEM_TYPE 151 
#define  DEMANGLE_COMPONENT_QUAL_NAME 150 
#define  DEMANGLE_COMPONENT_REFERENCE 149 
#define  DEMANGLE_COMPONENT_REFTEMP 148 
#define  DEMANGLE_COMPONENT_RESTRICT 147 
#define  DEMANGLE_COMPONENT_RESTRICT_THIS 146 
#define  DEMANGLE_COMPONENT_TEMPLATE 145 
#define  DEMANGLE_COMPONENT_TEMPLATE_ARGLIST 144 
#define  DEMANGLE_COMPONENT_THUNK 143 
#define  DEMANGLE_COMPONENT_TRINARY 142 
#define  DEMANGLE_COMPONENT_TRINARY_ARG1 141 
#define  DEMANGLE_COMPONENT_TRINARY_ARG2 140 
#define  DEMANGLE_COMPONENT_TYPED_NAME 139 
#define  DEMANGLE_COMPONENT_TYPEINFO 138 
#define  DEMANGLE_COMPONENT_TYPEINFO_FN 137 
#define  DEMANGLE_COMPONENT_TYPEINFO_NAME 136 
#define  DEMANGLE_COMPONENT_UNARY 135 
#define  DEMANGLE_COMPONENT_VENDOR_TYPE 134 
#define  DEMANGLE_COMPONENT_VENDOR_TYPE_QUAL 133 
#define  DEMANGLE_COMPONENT_VIRTUAL_THUNK 132 
#define  DEMANGLE_COMPONENT_VOLATILE 131 
#define  DEMANGLE_COMPONENT_VOLATILE_THIS 130 
#define  DEMANGLE_COMPONENT_VTABLE 129 
#define  DEMANGLE_COMPONENT_VTT 128 
 struct demangle_component* d_make_empty (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_make_comp (struct d_info *di, enum demangle_component_type type,
             struct demangle_component *left,
             struct demangle_component *right)
{
  struct demangle_component *p;

  /* We check for errors here.  A typical error would be a NULL return
     from a subroutine.  We catch those here, and return NULL
     upward.  */
  switch (type)
    {
      /* These types require two parameters.  */
    case DEMANGLE_COMPONENT_QUAL_NAME:
    case DEMANGLE_COMPONENT_LOCAL_NAME:
    case DEMANGLE_COMPONENT_TYPED_NAME:
    case DEMANGLE_COMPONENT_TEMPLATE:
    case DEMANGLE_COMPONENT_CONSTRUCTION_VTABLE:
    case DEMANGLE_COMPONENT_VENDOR_TYPE_QUAL:
    case DEMANGLE_COMPONENT_PTRMEM_TYPE:
    case DEMANGLE_COMPONENT_UNARY:
    case DEMANGLE_COMPONENT_BINARY:
    case DEMANGLE_COMPONENT_BINARY_ARGS:
    case DEMANGLE_COMPONENT_TRINARY:
    case DEMANGLE_COMPONENT_TRINARY_ARG1:
    case DEMANGLE_COMPONENT_TRINARY_ARG2:
    case DEMANGLE_COMPONENT_LITERAL:
    case DEMANGLE_COMPONENT_LITERAL_NEG:
      if (left == NULL || right == NULL)
	return NULL;
      break;

      /* These types only require one parameter.  */
    case DEMANGLE_COMPONENT_VTABLE:
    case DEMANGLE_COMPONENT_VTT:
    case DEMANGLE_COMPONENT_TYPEINFO:
    case DEMANGLE_COMPONENT_TYPEINFO_NAME:
    case DEMANGLE_COMPONENT_TYPEINFO_FN:
    case DEMANGLE_COMPONENT_THUNK:
    case DEMANGLE_COMPONENT_VIRTUAL_THUNK:
    case DEMANGLE_COMPONENT_COVARIANT_THUNK:
    case DEMANGLE_COMPONENT_JAVA_CLASS:
    case DEMANGLE_COMPONENT_GUARD:
    case DEMANGLE_COMPONENT_REFTEMP:
    case DEMANGLE_COMPONENT_HIDDEN_ALIAS:
    case DEMANGLE_COMPONENT_POINTER:
    case DEMANGLE_COMPONENT_REFERENCE:
    case DEMANGLE_COMPONENT_COMPLEX:
    case DEMANGLE_COMPONENT_IMAGINARY:
    case DEMANGLE_COMPONENT_VENDOR_TYPE:
    case DEMANGLE_COMPONENT_ARGLIST:
    case DEMANGLE_COMPONENT_TEMPLATE_ARGLIST:
    case DEMANGLE_COMPONENT_CAST:
      if (left == NULL)
	return NULL;
      break;

      /* This needs a right parameter, but the left parameter can be
	 empty.  */
    case DEMANGLE_COMPONENT_ARRAY_TYPE:
      if (right == NULL)
	return NULL;
      break;

      /* These are allowed to have no parameters--in some cases they
	 will be filled in later.  */
    case DEMANGLE_COMPONENT_FUNCTION_TYPE:
    case DEMANGLE_COMPONENT_RESTRICT:
    case DEMANGLE_COMPONENT_VOLATILE:
    case DEMANGLE_COMPONENT_CONST:
    case DEMANGLE_COMPONENT_RESTRICT_THIS:
    case DEMANGLE_COMPONENT_VOLATILE_THIS:
    case DEMANGLE_COMPONENT_CONST_THIS:
      break;

      /* Other types should not be seen here.  */
    default:
      return NULL;
    }

  p = d_make_empty (di);
  if (p != NULL)
    {
      p->type = type;
      p->u.s_binary.left = left;
      p->u.s_binary.right = right;
    }
  return p;
}