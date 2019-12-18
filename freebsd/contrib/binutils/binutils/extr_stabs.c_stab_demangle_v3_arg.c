#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stab_handle {int dummy; } ;
struct TYPE_7__ {struct demangle_component* right; struct demangle_component* left; } ;
struct TYPE_6__ {char* string; int len; } ;
struct TYPE_5__ {int len; char* s; } ;
struct TYPE_8__ {TYPE_3__ s_binary; TYPE_2__ s_string; TYPE_1__ s_name; } ;
struct demangle_component {int type; TYPE_4__ u; } ;
typedef  int /*<<< orphan*/ * debug_type ;
typedef  int /*<<< orphan*/  debug_field ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  const DEBUG_FIELD_NULL ; 
 int /*<<< orphan*/  DEBUG_KIND_CLASS ; 
 int /*<<< orphan*/  DEBUG_KIND_ILLEGAL ; 
#define  DEMANGLE_COMPONENT_ARGLIST 154 
#define  DEMANGLE_COMPONENT_ARRAY_TYPE 153 
#define  DEMANGLE_COMPONENT_BUILTIN_TYPE 152 
#define  DEMANGLE_COMPONENT_COMPLEX 151 
#define  DEMANGLE_COMPONENT_CONST 150 
#define  DEMANGLE_COMPONENT_CONST_THIS 149 
#define  DEMANGLE_COMPONENT_CTOR 148 
#define  DEMANGLE_COMPONENT_DTOR 147 
#define  DEMANGLE_COMPONENT_FUNCTION_TYPE 146 
#define  DEMANGLE_COMPONENT_IMAGINARY 145 
#define  DEMANGLE_COMPONENT_JAVA_CLASS 144 
#define  DEMANGLE_COMPONENT_LOCAL_NAME 143 
#define  DEMANGLE_COMPONENT_NAME 142 
#define  DEMANGLE_COMPONENT_POINTER 141 
#define  DEMANGLE_COMPONENT_PTRMEM_TYPE 140 
#define  DEMANGLE_COMPONENT_QUAL_NAME 139 
#define  DEMANGLE_COMPONENT_REFERENCE 138 
#define  DEMANGLE_COMPONENT_RESTRICT 137 
#define  DEMANGLE_COMPONENT_RESTRICT_THIS 136 
#define  DEMANGLE_COMPONENT_SUB_STD 135 
#define  DEMANGLE_COMPONENT_TEMPLATE 134 
#define  DEMANGLE_COMPONENT_TEMPLATE_PARAM 133 
#define  DEMANGLE_COMPONENT_TYPED_NAME 132 
#define  DEMANGLE_COMPONENT_VENDOR_TYPE 131 
#define  DEMANGLE_COMPONENT_VENDOR_TYPE_QUAL 130 
#define  DEMANGLE_COMPONENT_VOLATILE 129 
#define  DEMANGLE_COMPONENT_VOLATILE_THIS 128 
 int DMGL_ANSI ; 
 int DMGL_PARAMS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 char* cplus_demangle_print (int,struct demangle_component*,int,size_t*) ; 
 int /*<<< orphan*/ * debug_get_field_type (void*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * debug_get_fields (void*,int /*<<< orphan*/ *) ; 
 char* debug_get_type_name (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * debug_make_bool_type (void*,int) ; 
 int /*<<< orphan*/ * debug_make_const_type (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * debug_make_float_type (void*,int) ; 
 int /*<<< orphan*/ * debug_make_function_type (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * debug_make_int_type (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * debug_make_pointer_type (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * debug_make_reference_type (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * debug_make_void_type (void*) ; 
 int /*<<< orphan*/ * debug_make_volatile_type (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ ** stab_demangle_v3_arglist (void*,struct stab_handle*,struct demangle_component*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stab_find_tagged_type (void*,struct stab_handle*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static debug_type
stab_demangle_v3_arg (void *dhandle, struct stab_handle *info,
		      struct demangle_component *dc, debug_type context,
		      bfd_boolean *pvarargs)
{
  debug_type dt;

  if (pvarargs != NULL)
    *pvarargs = FALSE;

  switch (dc->type)
    {
      /* FIXME: These are demangle component types which we probably
	 need to handle one way or another.  */
    case DEMANGLE_COMPONENT_LOCAL_NAME:
    case DEMANGLE_COMPONENT_TYPED_NAME:
    case DEMANGLE_COMPONENT_TEMPLATE_PARAM:
    case DEMANGLE_COMPONENT_CTOR:
    case DEMANGLE_COMPONENT_DTOR:
    case DEMANGLE_COMPONENT_JAVA_CLASS:
    case DEMANGLE_COMPONENT_RESTRICT_THIS:
    case DEMANGLE_COMPONENT_VOLATILE_THIS:
    case DEMANGLE_COMPONENT_CONST_THIS:
    case DEMANGLE_COMPONENT_VENDOR_TYPE_QUAL:
    case DEMANGLE_COMPONENT_COMPLEX:
    case DEMANGLE_COMPONENT_IMAGINARY:
    case DEMANGLE_COMPONENT_VENDOR_TYPE:
    case DEMANGLE_COMPONENT_ARRAY_TYPE:
    case DEMANGLE_COMPONENT_PTRMEM_TYPE:
    case DEMANGLE_COMPONENT_ARGLIST:
    default:
      fprintf (stderr, _("Unrecognized demangle component %d\n"),
	       (int) dc->type);
      return NULL;

    case DEMANGLE_COMPONENT_NAME:
      if (context != NULL)
	{
	  const debug_field *fields;

	  fields = debug_get_fields (dhandle, context);
	  if (fields != NULL)
	    {
	      /* Try to find this type by looking through the context
		 class.  */
	      for (; *fields != DEBUG_FIELD_NULL; fields++)
		{
		  debug_type ft;
		  const char *dn;

		  ft = debug_get_field_type (dhandle, *fields);
		  if (ft == NULL)
		    return NULL;
		  dn = debug_get_type_name (dhandle, ft);
		  if (dn != NULL
		      && (int) strlen (dn) == dc->u.s_name.len
		      && strncmp (dn, dc->u.s_name.s, dc->u.s_name.len) == 0)
		    return ft;
		}
	    }
	}
      return stab_find_tagged_type (dhandle, info, dc->u.s_name.s,
				    dc->u.s_name.len, DEBUG_KIND_ILLEGAL);

    case DEMANGLE_COMPONENT_QUAL_NAME:
      context = stab_demangle_v3_arg (dhandle, info, dc->u.s_binary.left,
				      context, NULL);
      if (context == NULL)
	return NULL;
      return stab_demangle_v3_arg (dhandle, info, dc->u.s_binary.right,
				   context, NULL);

    case DEMANGLE_COMPONENT_TEMPLATE:
      {
	char *p;
	size_t alc;

	/* We print this component to get a class name which we can
	   use.  FIXME: This probably won't work if the template uses
	   template parameters which refer to an outer template.  */
	p = cplus_demangle_print (DMGL_PARAMS | DMGL_ANSI, dc, 20, &alc);
	if (p == NULL)
	  {
	    fprintf (stderr, _("Failed to print demangled template\n"));
	    return NULL;
	  }
	dt = stab_find_tagged_type (dhandle, info, p, strlen (p),
				    DEBUG_KIND_CLASS);
	free (p);
	return dt;
      }

    case DEMANGLE_COMPONENT_SUB_STD:
      return stab_find_tagged_type (dhandle, info, dc->u.s_string.string,
				    dc->u.s_string.len, DEBUG_KIND_ILLEGAL);

    case DEMANGLE_COMPONENT_RESTRICT:
    case DEMANGLE_COMPONENT_VOLATILE:
    case DEMANGLE_COMPONENT_CONST:
    case DEMANGLE_COMPONENT_POINTER:
    case DEMANGLE_COMPONENT_REFERENCE:
      dt = stab_demangle_v3_arg (dhandle, info, dc->u.s_binary.left, NULL,
				 NULL);
      if (dt == NULL)
	return NULL;

      switch (dc->type)
	{
	default:
	  abort ();
	case DEMANGLE_COMPONENT_RESTRICT:
	  /* FIXME: We have no way to represent restrict.  */
	  return dt;
	case DEMANGLE_COMPONENT_VOLATILE:
	  return debug_make_volatile_type (dhandle, dt);
	case DEMANGLE_COMPONENT_CONST:
	  return debug_make_const_type (dhandle, dt);
	case DEMANGLE_COMPONENT_POINTER:
	  return debug_make_pointer_type (dhandle, dt);
	case DEMANGLE_COMPONENT_REFERENCE:
	  return debug_make_reference_type (dhandle, dt);
	}

    case DEMANGLE_COMPONENT_FUNCTION_TYPE:
      {
	debug_type *pargs;
	bfd_boolean varargs;

	if (dc->u.s_binary.left == NULL)
	  {
	    /* In this case the return type is actually unknown.
	       However, I'm not sure this will ever arise in practice;
	       normally an unknown return type would only appear at
	       the top level, which is handled above.  */
	    dt = debug_make_void_type (dhandle);
	  }
	else
	  dt = stab_demangle_v3_arg (dhandle, info, dc->u.s_binary.left, NULL,
				     NULL);
	if (dt == NULL)
	  return NULL;

	pargs = stab_demangle_v3_arglist (dhandle, info,
					  dc->u.s_binary.right,
					  &varargs);
	if (pargs == NULL)
	  return NULL;

	return debug_make_function_type (dhandle, dt, pargs, varargs);
      }

    case DEMANGLE_COMPONENT_BUILTIN_TYPE:
      {
	char *p;
	size_t alc;
	debug_type ret;

	/* We print this component in order to find out the type name.
	   FIXME: Should we instead expose the
	   demangle_builtin_type_info structure?  */
	p = cplus_demangle_print (DMGL_PARAMS | DMGL_ANSI, dc, 20, &alc);
	if (p == NULL)
	  {
	    fprintf (stderr, _("Couldn't get demangled builtin type\n"));
	    return NULL;
	  }

	/* The mangling is based on the type, but does not itself
	   indicate what the sizes are.  So we have to guess.  */
	if (strcmp (p, "signed char") == 0)
	  ret = debug_make_int_type (dhandle, 1, FALSE);
	else if (strcmp (p, "bool") == 0)
	  ret = debug_make_bool_type (dhandle, 1);
	else if (strcmp (p, "char") == 0)
	  ret = debug_make_int_type (dhandle, 1, FALSE);
	else if (strcmp (p, "double") == 0)
	  ret = debug_make_float_type (dhandle, 8);
	else if (strcmp (p, "long double") == 0)
	  ret = debug_make_float_type (dhandle, 8);
	else if (strcmp (p, "float") == 0)
	  ret = debug_make_float_type (dhandle, 4);
	else if (strcmp (p, "__float128") == 0)
	  ret = debug_make_float_type (dhandle, 16);
	else if (strcmp (p, "unsigned char") == 0)
	  ret = debug_make_int_type (dhandle, 1, TRUE);
	else if (strcmp (p, "int") == 0)
	  ret = debug_make_int_type (dhandle, 4, FALSE);
	else if (strcmp (p, "unsigned int") == 0)
	  ret = debug_make_int_type (dhandle, 4, TRUE);
	else if (strcmp (p, "long") == 0)
	  ret = debug_make_int_type (dhandle, 4, FALSE);
	else if (strcmp (p, "unsigned long") == 0)
	  ret = debug_make_int_type (dhandle, 4, TRUE);
	else if (strcmp (p, "__int128") == 0)
	  ret = debug_make_int_type (dhandle, 16, FALSE);
	else if (strcmp (p, "unsigned __int128") == 0)
	  ret = debug_make_int_type (dhandle, 16, TRUE);
	else if (strcmp (p, "short") == 0)
	  ret = debug_make_int_type (dhandle, 2, FALSE);
	else if (strcmp (p, "unsigned short") == 0)
	  ret = debug_make_int_type (dhandle, 2, TRUE);
	else if (strcmp (p, "void") == 0)
	  ret = debug_make_void_type (dhandle);
	else if (strcmp (p, "wchar_t") == 0)
	  ret = debug_make_int_type (dhandle, 4, TRUE);
	else if (strcmp (p, "long long") == 0)
	  ret = debug_make_int_type (dhandle, 8, FALSE);
	else if (strcmp (p, "unsigned long long") == 0)
	  ret = debug_make_int_type (dhandle, 8, TRUE);
	else if (strcmp (p, "...") == 0)
	  {
	    if (pvarargs == NULL)
	      fprintf (stderr, _("Unexpected demangled varargs\n"));
	    else
	      *pvarargs = TRUE;
	    ret = NULL;
	  }
	else
	  {
	    fprintf (stderr, _("Unrecognized demangled builtin type\n"));
	    ret = NULL;
	  }

	free (p);

	return ret;
      }
    }
}