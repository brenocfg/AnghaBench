#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* type; } ;
struct TYPE_6__ {TYPE_2__ s_builtin; } ;
struct demangle_component {int /*<<< orphan*/  type; TYPE_3__ u; } ;
struct d_info {int /*<<< orphan*/  expansion; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMANGLE_COMPONENT_COMPLEX ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_IMAGINARY ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_POINTER ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_REFERENCE ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_SUB_STD ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_TEMPLATE ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_VENDOR_TYPE ; 
 int /*<<< orphan*/  DEMANGLE_COMPONENT_VENDOR_TYPE_QUAL ; 
 int /*<<< orphan*/  IS_DIGIT (char) ; 
 int /*<<< orphan*/  IS_UPPER (char) ; 
 int /*<<< orphan*/ * cplus_demangle_builtin_types ; 
 int /*<<< orphan*/  d_add_substitution (struct d_info*,struct demangle_component*) ; 
 int /*<<< orphan*/  d_advance (struct d_info*,int) ; 
 struct demangle_component* d_array_type (struct d_info*) ; 
 struct demangle_component* d_class_enum_type (struct d_info*) ; 
 struct demangle_component** d_cv_qualifiers (struct d_info*,struct demangle_component**,int /*<<< orphan*/ ) ; 
 struct demangle_component* d_function_type (struct d_info*) ; 
 struct demangle_component* d_make_builtin_type (struct d_info*,int /*<<< orphan*/ *) ; 
 struct demangle_component* d_make_comp (struct d_info*,int /*<<< orphan*/ ,struct demangle_component*,struct demangle_component*) ; 
 char d_peek_char (struct d_info*) ; 
 char d_peek_next_char (struct d_info*) ; 
 struct demangle_component* d_pointer_to_member_type (struct d_info*) ; 
 struct demangle_component* d_source_name (struct d_info*) ; 
 struct demangle_component* d_substitution (struct d_info*,int /*<<< orphan*/ ) ; 
 struct demangle_component* d_template_args (struct d_info*) ; 
 struct demangle_component* d_template_param (struct d_info*) ; 

struct demangle_component *
cplus_demangle_type (struct d_info *di)
{
  char peek;
  struct demangle_component *ret;
  int can_subst;

  /* The ABI specifies that when CV-qualifiers are used, the base type
     is substitutable, and the fully qualified type is substitutable,
     but the base type with a strict subset of the CV-qualifiers is
     not substitutable.  The natural recursive implementation of the
     CV-qualifiers would cause subsets to be substitutable, so instead
     we pull them all off now.

     FIXME: The ABI says that order-insensitive vendor qualifiers
     should be handled in the same way, but we have no way to tell
     which vendor qualifiers are order-insensitive and which are
     order-sensitive.  So we just assume that they are all
     order-sensitive.  g++ 3.4 supports only one vendor qualifier,
     __vector, and it treats it as order-sensitive when mangling
     names.  */

  peek = d_peek_char (di);
  if (peek == 'r' || peek == 'V' || peek == 'K')
    {
      struct demangle_component **pret;

      pret = d_cv_qualifiers (di, &ret, 0);
      if (pret == NULL)
	return NULL;
      *pret = cplus_demangle_type (di);
      if (! *pret || ! d_add_substitution (di, ret))
	return NULL;
      return ret;
    }

  can_subst = 1;

  switch (peek)
    {
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
    case 'h': case 'i': case 'j':           case 'l': case 'm': case 'n':
    case 'o':                               case 's': case 't':
    case 'v': case 'w': case 'x': case 'y': case 'z':
      ret = d_make_builtin_type (di,
				 &cplus_demangle_builtin_types[peek - 'a']);
      di->expansion += ret->u.s_builtin.type->len;
      can_subst = 0;
      d_advance (di, 1);
      break;

    case 'u':
      d_advance (di, 1);
      ret = d_make_comp (di, DEMANGLE_COMPONENT_VENDOR_TYPE,
			 d_source_name (di), NULL);
      break;

    case 'F':
      ret = d_function_type (di);
      break;

    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    case 'N':
    case 'Z':
      ret = d_class_enum_type (di);
      break;

    case 'A':
      ret = d_array_type (di);
      break;

    case 'M':
      ret = d_pointer_to_member_type (di);
      break;

    case 'T':
      ret = d_template_param (di);
      if (d_peek_char (di) == 'I')
	{
	  /* This is <template-template-param> <template-args>.  The
	     <template-template-param> part is a substitution
	     candidate.  */
	  if (! d_add_substitution (di, ret))
	    return NULL;
	  ret = d_make_comp (di, DEMANGLE_COMPONENT_TEMPLATE, ret,
			     d_template_args (di));
	}
      break;

    case 'S':
      /* If this is a special substitution, then it is the start of
	 <class-enum-type>.  */
      {
	char peek_next;

	peek_next = d_peek_next_char (di);
	if (IS_DIGIT (peek_next)
	    || peek_next == '_'
	    || IS_UPPER (peek_next))
	  {
	    ret = d_substitution (di, 0);
	    /* The substituted name may have been a template name and
	       may be followed by tepmlate args.  */
	    if (d_peek_char (di) == 'I')
	      ret = d_make_comp (di, DEMANGLE_COMPONENT_TEMPLATE, ret,
				 d_template_args (di));
	    else
	      can_subst = 0;
	  }
	else
	  {
	    ret = d_class_enum_type (di);
	    /* If the substitution was a complete type, then it is not
	       a new substitution candidate.  However, if the
	       substitution was followed by template arguments, then
	       the whole thing is a substitution candidate.  */
	    if (ret != NULL && ret->type == DEMANGLE_COMPONENT_SUB_STD)
	      can_subst = 0;
	  }
      }
      break;

    case 'P':
      d_advance (di, 1);
      ret = d_make_comp (di, DEMANGLE_COMPONENT_POINTER,
			 cplus_demangle_type (di), NULL);
      break;

    case 'R':
      d_advance (di, 1);
      ret = d_make_comp (di, DEMANGLE_COMPONENT_REFERENCE,
			 cplus_demangle_type (di), NULL);
      break;

    case 'C':
      d_advance (di, 1);
      ret = d_make_comp (di, DEMANGLE_COMPONENT_COMPLEX,
			 cplus_demangle_type (di), NULL);
      break;

    case 'G':
      d_advance (di, 1);
      ret = d_make_comp (di, DEMANGLE_COMPONENT_IMAGINARY,
			 cplus_demangle_type (di), NULL);
      break;

    case 'U':
      d_advance (di, 1);
      ret = d_source_name (di);
      ret = d_make_comp (di, DEMANGLE_COMPONENT_VENDOR_TYPE_QUAL,
			 cplus_demangle_type (di), ret);
      break;

    default:
      return NULL;
    }

  if (can_subst)
    {
      if (! d_add_substitution (di, ret))
	return NULL;
    }

  return ret;
}