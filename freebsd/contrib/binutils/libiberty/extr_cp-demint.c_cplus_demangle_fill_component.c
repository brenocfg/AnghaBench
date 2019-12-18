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
typedef  enum demangle_component_type { ____Placeholder_demangle_component_type } demangle_component_type ;

/* Variables and functions */
#define  DEMANGLE_COMPONENT_ARGLIST 169 
#define  DEMANGLE_COMPONENT_ARRAY_TYPE 168 
#define  DEMANGLE_COMPONENT_BINARY 167 
#define  DEMANGLE_COMPONENT_BINARY_ARGS 166 
#define  DEMANGLE_COMPONENT_CAST 165 
#define  DEMANGLE_COMPONENT_COMPLEX 164 
#define  DEMANGLE_COMPONENT_CONST 163 
#define  DEMANGLE_COMPONENT_CONSTRUCTION_VTABLE 162 
#define  DEMANGLE_COMPONENT_CONST_THIS 161 
#define  DEMANGLE_COMPONENT_COVARIANT_THUNK 160 
#define  DEMANGLE_COMPONENT_FUNCTION_TYPE 159 
#define  DEMANGLE_COMPONENT_GUARD 158 
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

int
cplus_demangle_fill_component (struct demangle_component *p,
                               enum demangle_component_type type,
                               struct demangle_component *left,
                                struct demangle_component *right)
{
  if (p == NULL)
    return 0;
  switch (type)
    {
    case DEMANGLE_COMPONENT_QUAL_NAME:
    case DEMANGLE_COMPONENT_LOCAL_NAME:
    case DEMANGLE_COMPONENT_TYPED_NAME:
    case DEMANGLE_COMPONENT_TEMPLATE:
    case DEMANGLE_COMPONENT_CONSTRUCTION_VTABLE:
    case DEMANGLE_COMPONENT_VENDOR_TYPE_QUAL:
    case DEMANGLE_COMPONENT_FUNCTION_TYPE:
    case DEMANGLE_COMPONENT_ARRAY_TYPE:
    case DEMANGLE_COMPONENT_PTRMEM_TYPE:
    case DEMANGLE_COMPONENT_ARGLIST:
    case DEMANGLE_COMPONENT_TEMPLATE_ARGLIST:
    case DEMANGLE_COMPONENT_UNARY:
    case DEMANGLE_COMPONENT_BINARY:
    case DEMANGLE_COMPONENT_BINARY_ARGS:
    case DEMANGLE_COMPONENT_TRINARY:
    case DEMANGLE_COMPONENT_TRINARY_ARG1:
    case DEMANGLE_COMPONENT_TRINARY_ARG2:
    case DEMANGLE_COMPONENT_LITERAL:
    case DEMANGLE_COMPONENT_LITERAL_NEG:
      break;

      /* These component types only have one subtree.  */
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
    case DEMANGLE_COMPONENT_RESTRICT:
    case DEMANGLE_COMPONENT_VOLATILE:
    case DEMANGLE_COMPONENT_CONST:
    case DEMANGLE_COMPONENT_RESTRICT_THIS:
    case DEMANGLE_COMPONENT_VOLATILE_THIS:
    case DEMANGLE_COMPONENT_CONST_THIS:
    case DEMANGLE_COMPONENT_POINTER:
    case DEMANGLE_COMPONENT_REFERENCE:
    case DEMANGLE_COMPONENT_COMPLEX:
    case DEMANGLE_COMPONENT_IMAGINARY:
    case DEMANGLE_COMPONENT_VENDOR_TYPE:
    case DEMANGLE_COMPONENT_CAST:
      if (right != NULL)
	return 0;
      break;

    default:
      /* Other types do not use subtrees.  */
      return 0;
    }

  p->type = type;
  p->u.s_binary.left = left;
  p->u.s_binary.right = right;

  return 1;
}