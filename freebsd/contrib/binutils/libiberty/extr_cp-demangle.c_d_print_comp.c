#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_12__ {char* s; int len; } ;
struct TYPE_22__ {TYPE_8__* type; } ;
struct TYPE_20__ {TYPE_6__* op; } ;
struct TYPE_18__ {struct demangle_component const* name; } ;
struct TYPE_17__ {char* string; int len; } ;
struct TYPE_16__ {struct demangle_component const* name; } ;
struct TYPE_15__ {struct demangle_component const* name; } ;
struct TYPE_14__ {long number; } ;
struct TYPE_13__ {TYPE_10__ s_name; TYPE_9__ s_builtin; TYPE_7__ s_operator; TYPE_5__ s_extended_operator; TYPE_4__ s_string; TYPE_3__ s_dtor; TYPE_2__ s_ctor; TYPE_1__ s_number; } ;
typedef  struct demangle_component {int type; TYPE_11__ u; } const demangle_component ;
struct d_print_template {struct d_print_template* next; struct demangle_component const* template_decl; } ;
struct d_print_mod {int printed; struct d_print_mod* next; struct d_print_template* templates; struct demangle_component const* mod; } ;
struct d_print_info {int options; struct d_print_mod* modifiers; struct d_print_template* templates; } ;
typedef  enum d_builtin_type_print { ____Placeholder_d_builtin_type_print } d_builtin_type_print ;
struct TYPE_21__ {char* name; int len; char* java_name; int java_len; int print; } ;
struct TYPE_19__ {char* name; int len; } ;

/* Variables and functions */
#define  DEMANGLE_COMPONENT_ARGLIST 185 
#define  DEMANGLE_COMPONENT_ARRAY_TYPE 184 
#define  DEMANGLE_COMPONENT_BINARY 183 
#define  DEMANGLE_COMPONENT_BINARY_ARGS 182 
#define  DEMANGLE_COMPONENT_BUILTIN_TYPE 181 
#define  DEMANGLE_COMPONENT_CAST 180 
#define  DEMANGLE_COMPONENT_COMPLEX 179 
#define  DEMANGLE_COMPONENT_CONST 178 
#define  DEMANGLE_COMPONENT_CONSTRUCTION_VTABLE 177 
#define  DEMANGLE_COMPONENT_CONST_THIS 176 
#define  DEMANGLE_COMPONENT_COVARIANT_THUNK 175 
#define  DEMANGLE_COMPONENT_CTOR 174 
#define  DEMANGLE_COMPONENT_DTOR 173 
#define  DEMANGLE_COMPONENT_EXTENDED_OPERATOR 172 
#define  DEMANGLE_COMPONENT_FUNCTION_TYPE 171 
#define  DEMANGLE_COMPONENT_GUARD 170 
#define  DEMANGLE_COMPONENT_HIDDEN_ALIAS 169 
#define  DEMANGLE_COMPONENT_IMAGINARY 168 
#define  DEMANGLE_COMPONENT_JAVA_CLASS 167 
#define  DEMANGLE_COMPONENT_LITERAL 166 
#define  DEMANGLE_COMPONENT_LITERAL_NEG 165 
#define  DEMANGLE_COMPONENT_LOCAL_NAME 164 
#define  DEMANGLE_COMPONENT_NAME 163 
#define  DEMANGLE_COMPONENT_OPERATOR 162 
#define  DEMANGLE_COMPONENT_POINTER 161 
#define  DEMANGLE_COMPONENT_PTRMEM_TYPE 160 
#define  DEMANGLE_COMPONENT_QUAL_NAME 159 
#define  DEMANGLE_COMPONENT_REFERENCE 158 
#define  DEMANGLE_COMPONENT_REFTEMP 157 
#define  DEMANGLE_COMPONENT_RESTRICT 156 
#define  DEMANGLE_COMPONENT_RESTRICT_THIS 155 
#define  DEMANGLE_COMPONENT_SUB_STD 154 
#define  DEMANGLE_COMPONENT_TEMPLATE 153 
#define  DEMANGLE_COMPONENT_TEMPLATE_ARGLIST 152 
#define  DEMANGLE_COMPONENT_TEMPLATE_PARAM 151 
#define  DEMANGLE_COMPONENT_THUNK 150 
#define  DEMANGLE_COMPONENT_TRINARY 149 
#define  DEMANGLE_COMPONENT_TRINARY_ARG1 148 
#define  DEMANGLE_COMPONENT_TRINARY_ARG2 147 
#define  DEMANGLE_COMPONENT_TYPED_NAME 146 
#define  DEMANGLE_COMPONENT_TYPEINFO 145 
#define  DEMANGLE_COMPONENT_TYPEINFO_FN 144 
#define  DEMANGLE_COMPONENT_TYPEINFO_NAME 143 
#define  DEMANGLE_COMPONENT_UNARY 142 
#define  DEMANGLE_COMPONENT_VENDOR_TYPE 141 
#define  DEMANGLE_COMPONENT_VENDOR_TYPE_QUAL 140 
#define  DEMANGLE_COMPONENT_VIRTUAL_THUNK 139 
#define  DEMANGLE_COMPONENT_VOLATILE 138 
#define  DEMANGLE_COMPONENT_VOLATILE_THIS 137 
#define  DEMANGLE_COMPONENT_VTABLE 136 
#define  DEMANGLE_COMPONENT_VTT 135 
 int DMGL_JAVA ; 
 int DMGL_RET_POSTFIX ; 
#define  D_PRINT_BOOL 134 
 int D_PRINT_DEFAULT ; 
 int D_PRINT_FLOAT ; 
#define  D_PRINT_INT 133 
#define  D_PRINT_LONG 132 
#define  D_PRINT_LONG_LONG 131 
#define  D_PRINT_UNSIGNED 130 
#define  D_PRINT_UNSIGNED_LONG 129 
#define  D_PRINT_UNSIGNED_LONG_LONG 128 
 int /*<<< orphan*/  IS_LOWER (char) ; 
 int /*<<< orphan*/  d_append_buffer (struct d_print_info*,char*,int) ; 
 int /*<<< orphan*/  d_append_char (struct d_print_info*,char) ; 
 int /*<<< orphan*/  d_append_string (struct d_print_info*,char*) ; 
 char d_last_char (struct d_print_info*) ; 
 struct demangle_component const* d_left (struct demangle_component const*) ; 
 int /*<<< orphan*/  d_print_array_type (struct d_print_info*,struct demangle_component const*,struct d_print_mod*) ; 
 int /*<<< orphan*/  d_print_cast (struct d_print_info*,struct demangle_component const*) ; 
 int /*<<< orphan*/  d_print_error (struct d_print_info*) ; 
 int /*<<< orphan*/  d_print_expr_op (struct d_print_info*,struct demangle_component const*) ; 
 int /*<<< orphan*/  d_print_function_type (struct d_print_info*,struct demangle_component const*,struct d_print_mod*) ; 
 int /*<<< orphan*/  d_print_java_identifier (struct d_print_info*,char*,int) ; 
 int /*<<< orphan*/  d_print_mod (struct d_print_info*,struct demangle_component const*) ; 
 scalar_t__ d_print_saw_error (struct d_print_info*) ; 
 struct demangle_component const* d_right (struct demangle_component const*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void
d_print_comp (struct d_print_info *dpi,
              const struct demangle_component *dc)
{
  if (dc == NULL)
    {
      d_print_error (dpi);
      return;
    }
  if (d_print_saw_error (dpi))
    return;

  switch (dc->type)
    {
    case DEMANGLE_COMPONENT_NAME:
      if ((dpi->options & DMGL_JAVA) == 0)
	d_append_buffer (dpi, dc->u.s_name.s, dc->u.s_name.len);
      else
	d_print_java_identifier (dpi, dc->u.s_name.s, dc->u.s_name.len);
      return;

    case DEMANGLE_COMPONENT_QUAL_NAME:
    case DEMANGLE_COMPONENT_LOCAL_NAME:
      d_print_comp (dpi, d_left (dc));
      if ((dpi->options & DMGL_JAVA) == 0)
	d_append_string (dpi, "::");
      else
	d_append_char (dpi, '.');
      d_print_comp (dpi, d_right (dc));
      return;

    case DEMANGLE_COMPONENT_TYPED_NAME:
      {
	struct d_print_mod *hold_modifiers;
	struct demangle_component *typed_name;
	struct d_print_mod adpm[4];
	unsigned int i;
	struct d_print_template dpt;

	/* Pass the name down to the type so that it can be printed in
	   the right place for the type.  We also have to pass down
	   any CV-qualifiers, which apply to the this parameter.  */
	hold_modifiers = dpi->modifiers;
	i = 0;
	typed_name = d_left (dc);
	while (typed_name != NULL)
	  {
	    if (i >= sizeof adpm / sizeof adpm[0])
	      {
		d_print_error (dpi);
		return;
	      }

	    adpm[i].next = dpi->modifiers;
	    dpi->modifiers = &adpm[i];
	    adpm[i].mod = typed_name;
	    adpm[i].printed = 0;
	    adpm[i].templates = dpi->templates;
	    ++i;

	    if (typed_name->type != DEMANGLE_COMPONENT_RESTRICT_THIS
		&& typed_name->type != DEMANGLE_COMPONENT_VOLATILE_THIS
		&& typed_name->type != DEMANGLE_COMPONENT_CONST_THIS)
	      break;

	    typed_name = d_left (typed_name);
	  }

	/* If typed_name is a template, then it applies to the
	   function type as well.  */
	if (typed_name->type == DEMANGLE_COMPONENT_TEMPLATE)
	  {
	    dpt.next = dpi->templates;
	    dpi->templates = &dpt;
	    dpt.template_decl = typed_name;
	  }

	/* If typed_name is a DEMANGLE_COMPONENT_LOCAL_NAME, then
	   there may be CV-qualifiers on its right argument which
	   really apply here; this happens when parsing a class which
	   is local to a function.  */
	if (typed_name->type == DEMANGLE_COMPONENT_LOCAL_NAME)
	  {
	    struct demangle_component *local_name;

	    local_name = d_right (typed_name);
	    while (local_name->type == DEMANGLE_COMPONENT_RESTRICT_THIS
		   || local_name->type == DEMANGLE_COMPONENT_VOLATILE_THIS
		   || local_name->type == DEMANGLE_COMPONENT_CONST_THIS)
	      {
		if (i >= sizeof adpm / sizeof adpm[0])
		  {
		    d_print_error (dpi);
		    return;
		  }

		adpm[i] = adpm[i - 1];
		adpm[i].next = &adpm[i - 1];
		dpi->modifiers = &adpm[i];

		adpm[i - 1].mod = local_name;
		adpm[i - 1].printed = 0;
		adpm[i - 1].templates = dpi->templates;
		++i;

		local_name = d_left (local_name);
	      }
	  }

	d_print_comp (dpi, d_right (dc));

	if (typed_name->type == DEMANGLE_COMPONENT_TEMPLATE)
	  dpi->templates = dpt.next;

	/* If the modifiers didn't get printed by the type, print them
	   now.  */
	while (i > 0)
	  {
	    --i;
	    if (! adpm[i].printed)
	      {
		d_append_char (dpi, ' ');
		d_print_mod (dpi, adpm[i].mod);
	      }
	  }

	dpi->modifiers = hold_modifiers;

	return;
      }

    case DEMANGLE_COMPONENT_TEMPLATE:
      {
	struct d_print_mod *hold_dpm;
	struct demangle_component *dcl;

	/* Don't push modifiers into a template definition.  Doing so
	   could give the wrong definition for a template argument.
	   Instead, treat the template essentially as a name.  */

	hold_dpm = dpi->modifiers;
	dpi->modifiers = NULL;

        dcl = d_left (dc);

        if ((dpi->options & DMGL_JAVA) != 0
            && dcl->type == DEMANGLE_COMPONENT_NAME
            && dcl->u.s_name.len == 6
            && strncmp (dcl->u.s_name.s, "JArray", 6) == 0)
          {
            /* Special-case Java arrays, so that JArray<TYPE> appears
               instead as TYPE[].  */

            d_print_comp (dpi, d_right (dc));
            d_append_string (dpi, "[]");
          }
        else
          {
	    d_print_comp (dpi, dcl);
	    if (d_last_char (dpi) == '<')
	      d_append_char (dpi, ' ');
	    d_append_char (dpi, '<');
	    d_print_comp (dpi, d_right (dc));
	    /* Avoid generating two consecutive '>' characters, to avoid
	       the C++ syntactic ambiguity.  */
	    if (d_last_char (dpi) == '>')
	      d_append_char (dpi, ' ');
	    d_append_char (dpi, '>');
          }

	dpi->modifiers = hold_dpm;

	return;
      }

    case DEMANGLE_COMPONENT_TEMPLATE_PARAM:
      {
	long i;
	struct demangle_component *a;
	struct d_print_template *hold_dpt;

	if (dpi->templates == NULL)
	  {
	    d_print_error (dpi);
	    return;
	  }
	i = dc->u.s_number.number;
	for (a = d_right (dpi->templates->template_decl);
	     a != NULL;
	     a = d_right (a))
	  {
	    if (a->type != DEMANGLE_COMPONENT_TEMPLATE_ARGLIST)
	      {
		d_print_error (dpi);
		return;
	      }
	    if (i <= 0)
	      break;
	    --i;
	  }
	if (i != 0 || a == NULL)
	  {
	    d_print_error (dpi);
	    return;
	  }

	/* While processing this parameter, we need to pop the list of
	   templates.  This is because the template parameter may
	   itself be a reference to a parameter of an outer
	   template.  */

	hold_dpt = dpi->templates;
	dpi->templates = hold_dpt->next;

	d_print_comp (dpi, d_left (a));

	dpi->templates = hold_dpt;

	return;
      }

    case DEMANGLE_COMPONENT_CTOR:
      d_print_comp (dpi, dc->u.s_ctor.name);
      return;

    case DEMANGLE_COMPONENT_DTOR:
      d_append_char (dpi, '~');
      d_print_comp (dpi, dc->u.s_dtor.name);
      return;

    case DEMANGLE_COMPONENT_VTABLE:
      d_append_string (dpi, "vtable for ");
      d_print_comp (dpi, d_left (dc));
      return;

    case DEMANGLE_COMPONENT_VTT:
      d_append_string (dpi, "VTT for ");
      d_print_comp (dpi, d_left (dc));
      return;

    case DEMANGLE_COMPONENT_CONSTRUCTION_VTABLE:
      d_append_string (dpi, "construction vtable for ");
      d_print_comp (dpi, d_left (dc));
      d_append_string (dpi, "-in-");
      d_print_comp (dpi, d_right (dc));
      return;

    case DEMANGLE_COMPONENT_TYPEINFO:
      d_append_string (dpi, "typeinfo for ");
      d_print_comp (dpi, d_left (dc));
      return;

    case DEMANGLE_COMPONENT_TYPEINFO_NAME:
      d_append_string (dpi, "typeinfo name for ");
      d_print_comp (dpi, d_left (dc));
      return;

    case DEMANGLE_COMPONENT_TYPEINFO_FN:
      d_append_string (dpi, "typeinfo fn for ");
      d_print_comp (dpi, d_left (dc));
      return;

    case DEMANGLE_COMPONENT_THUNK:
      d_append_string (dpi, "non-virtual thunk to ");
      d_print_comp (dpi, d_left (dc));
      return;

    case DEMANGLE_COMPONENT_VIRTUAL_THUNK:
      d_append_string (dpi, "virtual thunk to ");
      d_print_comp (dpi, d_left (dc));
      return;

    case DEMANGLE_COMPONENT_COVARIANT_THUNK:
      d_append_string (dpi, "covariant return thunk to ");
      d_print_comp (dpi, d_left (dc));
      return;

    case DEMANGLE_COMPONENT_JAVA_CLASS:
      d_append_string (dpi, "java Class for ");
      d_print_comp (dpi, d_left (dc));
      return;

    case DEMANGLE_COMPONENT_GUARD:
      d_append_string (dpi, "guard variable for ");
      d_print_comp (dpi, d_left (dc));
      return;

    case DEMANGLE_COMPONENT_REFTEMP:
      d_append_string (dpi, "reference temporary for ");
      d_print_comp (dpi, d_left (dc));
      return;

    case DEMANGLE_COMPONENT_HIDDEN_ALIAS:
      d_append_string (dpi, "hidden alias for ");
      d_print_comp (dpi, d_left (dc));
      return;

    case DEMANGLE_COMPONENT_SUB_STD:
      d_append_buffer (dpi, dc->u.s_string.string, dc->u.s_string.len);
      return;

    case DEMANGLE_COMPONENT_RESTRICT:
    case DEMANGLE_COMPONENT_VOLATILE:
    case DEMANGLE_COMPONENT_CONST:
      {
	struct d_print_mod *pdpm;

	/* When printing arrays, it's possible to have cases where the
	   same CV-qualifier gets pushed on the stack multiple times.
	   We only need to print it once.  */

	for (pdpm = dpi->modifiers; pdpm != NULL; pdpm = pdpm->next)
	  {
	    if (! pdpm->printed)
	      {
		if (pdpm->mod->type != DEMANGLE_COMPONENT_RESTRICT
		    && pdpm->mod->type != DEMANGLE_COMPONENT_VOLATILE
		    && pdpm->mod->type != DEMANGLE_COMPONENT_CONST)
		  break;
		if (pdpm->mod->type == dc->type)
		  {
		    d_print_comp (dpi, d_left (dc));
		    return;
		  }
	      }
	  }
      }
      /* Fall through.  */
    case DEMANGLE_COMPONENT_RESTRICT_THIS:
    case DEMANGLE_COMPONENT_VOLATILE_THIS:
    case DEMANGLE_COMPONENT_CONST_THIS:
    case DEMANGLE_COMPONENT_VENDOR_TYPE_QUAL:
    case DEMANGLE_COMPONENT_POINTER:
    case DEMANGLE_COMPONENT_REFERENCE:
    case DEMANGLE_COMPONENT_COMPLEX:
    case DEMANGLE_COMPONENT_IMAGINARY:
      {
	/* We keep a list of modifiers on the stack.  */
	struct d_print_mod dpm;

	dpm.next = dpi->modifiers;
	dpi->modifiers = &dpm;
	dpm.mod = dc;
	dpm.printed = 0;
	dpm.templates = dpi->templates;

	d_print_comp (dpi, d_left (dc));

	/* If the modifier didn't get printed by the type, print it
	   now.  */
	if (! dpm.printed)
	  d_print_mod (dpi, dc);

	dpi->modifiers = dpm.next;

	return;
      }

    case DEMANGLE_COMPONENT_BUILTIN_TYPE:
      if ((dpi->options & DMGL_JAVA) == 0)
	d_append_buffer (dpi, dc->u.s_builtin.type->name,
			 dc->u.s_builtin.type->len);
      else
	d_append_buffer (dpi, dc->u.s_builtin.type->java_name,
			 dc->u.s_builtin.type->java_len);
      return;

    case DEMANGLE_COMPONENT_VENDOR_TYPE:
      d_print_comp (dpi, d_left (dc));
      return;

    case DEMANGLE_COMPONENT_FUNCTION_TYPE:
      {
	if ((dpi->options & DMGL_RET_POSTFIX) != 0)
	  d_print_function_type (dpi, dc, dpi->modifiers);

	/* Print return type if present */
	if (d_left (dc) != NULL)
	  {
	    struct d_print_mod dpm;

	    /* We must pass this type down as a modifier in order to
	       print it in the right location.  */
	    dpm.next = dpi->modifiers;
	    dpi->modifiers = &dpm;
	    dpm.mod = dc;
	    dpm.printed = 0;
	    dpm.templates = dpi->templates;

	    d_print_comp (dpi, d_left (dc));

	    dpi->modifiers = dpm.next;

	    if (dpm.printed)
	      return;

	    /* In standard prefix notation, there is a space between the
	       return type and the function signature.  */
	    if ((dpi->options & DMGL_RET_POSTFIX) == 0)
	      d_append_char (dpi, ' ');
	  }

	if ((dpi->options & DMGL_RET_POSTFIX) == 0) 
	  d_print_function_type (dpi, dc, dpi->modifiers);

	return;
      }

    case DEMANGLE_COMPONENT_ARRAY_TYPE:
      {
	struct d_print_mod *hold_modifiers;
	struct d_print_mod adpm[4];
	unsigned int i;
	struct d_print_mod *pdpm;

	/* We must pass this type down as a modifier in order to print
	   multi-dimensional arrays correctly.  If the array itself is
	   CV-qualified, we act as though the element type were
	   CV-qualified.  We do this by copying the modifiers down
	   rather than fiddling pointers, so that we don't wind up
	   with a d_print_mod higher on the stack pointing into our
	   stack frame after we return.  */

	hold_modifiers = dpi->modifiers;

	adpm[0].next = hold_modifiers;
	dpi->modifiers = &adpm[0];
	adpm[0].mod = dc;
	adpm[0].printed = 0;
	adpm[0].templates = dpi->templates;

	i = 1;
	pdpm = hold_modifiers;
	while (pdpm != NULL
	       && (pdpm->mod->type == DEMANGLE_COMPONENT_RESTRICT
		   || pdpm->mod->type == DEMANGLE_COMPONENT_VOLATILE
		   || pdpm->mod->type == DEMANGLE_COMPONENT_CONST))
	  {
	    if (! pdpm->printed)
	      {
		if (i >= sizeof adpm / sizeof adpm[0])
		  {
		    d_print_error (dpi);
		    return;
		  }

		adpm[i] = *pdpm;
		adpm[i].next = dpi->modifiers;
		dpi->modifiers = &adpm[i];
		pdpm->printed = 1;
		++i;
	      }

	    pdpm = pdpm->next;
	  }

	d_print_comp (dpi, d_right (dc));

	dpi->modifiers = hold_modifiers;

	if (adpm[0].printed)
	  return;

	while (i > 1)
	  {
	    --i;
	    d_print_mod (dpi, adpm[i].mod);
	  }

	d_print_array_type (dpi, dc, dpi->modifiers);

	return;
      }

    case DEMANGLE_COMPONENT_PTRMEM_TYPE:
      {
	struct d_print_mod dpm;

	dpm.next = dpi->modifiers;
	dpi->modifiers = &dpm;
	dpm.mod = dc;
	dpm.printed = 0;
	dpm.templates = dpi->templates;

	d_print_comp (dpi, d_right (dc));

	/* If the modifier didn't get printed by the type, print it
	   now.  */
	if (! dpm.printed)
	  {
	    d_append_char (dpi, ' ');
	    d_print_comp (dpi, d_left (dc));
	    d_append_string (dpi, "::*");
	  }

	dpi->modifiers = dpm.next;

	return;
      }

    case DEMANGLE_COMPONENT_ARGLIST:
    case DEMANGLE_COMPONENT_TEMPLATE_ARGLIST:
      d_print_comp (dpi, d_left (dc));
      if (d_right (dc) != NULL)
	{
	  d_append_string (dpi, ", ");
	  d_print_comp (dpi, d_right (dc));
	}
      return;

    case DEMANGLE_COMPONENT_OPERATOR:
      {
	char c;

	d_append_string (dpi, "operator");
	c = dc->u.s_operator.op->name[0];
	if (IS_LOWER (c))
	  d_append_char (dpi, ' ');
	d_append_buffer (dpi, dc->u.s_operator.op->name,
			 dc->u.s_operator.op->len);
	return;
      }

    case DEMANGLE_COMPONENT_EXTENDED_OPERATOR:
      d_append_string (dpi, "operator ");
      d_print_comp (dpi, dc->u.s_extended_operator.name);
      return;

    case DEMANGLE_COMPONENT_CAST:
      d_append_string (dpi, "operator ");
      d_print_cast (dpi, dc);
      return;

    case DEMANGLE_COMPONENT_UNARY:
      if (d_left (dc)->type != DEMANGLE_COMPONENT_CAST)
	d_print_expr_op (dpi, d_left (dc));
      else
	{
	  d_append_char (dpi, '(');
	  d_print_cast (dpi, d_left (dc));
	  d_append_char (dpi, ')');
	}
      d_append_char (dpi, '(');
      d_print_comp (dpi, d_right (dc));
      d_append_char (dpi, ')');
      return;

    case DEMANGLE_COMPONENT_BINARY:
      if (d_right (dc)->type != DEMANGLE_COMPONENT_BINARY_ARGS)
	{
	  d_print_error (dpi);
	  return;
	}

      /* We wrap an expression which uses the greater-than operator in
	 an extra layer of parens so that it does not get confused
	 with the '>' which ends the template parameters.  */
      if (d_left (dc)->type == DEMANGLE_COMPONENT_OPERATOR
	  && d_left (dc)->u.s_operator.op->len == 1
	  && d_left (dc)->u.s_operator.op->name[0] == '>')
	d_append_char (dpi, '(');

      d_append_char (dpi, '(');
      d_print_comp (dpi, d_left (d_right (dc)));
      d_append_string (dpi, ") ");
      d_print_expr_op (dpi, d_left (dc));
      d_append_string (dpi, " (");
      d_print_comp (dpi, d_right (d_right (dc)));
      d_append_char (dpi, ')');

      if (d_left (dc)->type == DEMANGLE_COMPONENT_OPERATOR
	  && d_left (dc)->u.s_operator.op->len == 1
	  && d_left (dc)->u.s_operator.op->name[0] == '>')
	d_append_char (dpi, ')');

      return;

    case DEMANGLE_COMPONENT_BINARY_ARGS:
      /* We should only see this as part of DEMANGLE_COMPONENT_BINARY.  */
      d_print_error (dpi);
      return;

    case DEMANGLE_COMPONENT_TRINARY:
      if (d_right (dc)->type != DEMANGLE_COMPONENT_TRINARY_ARG1
	  || d_right (d_right (dc))->type != DEMANGLE_COMPONENT_TRINARY_ARG2)
	{
	  d_print_error (dpi);
	  return;
	}
      d_append_char (dpi, '(');
      d_print_comp (dpi, d_left (d_right (dc)));
      d_append_string (dpi, ") ");
      d_print_expr_op (dpi, d_left (dc));
      d_append_string (dpi, " (");
      d_print_comp (dpi, d_left (d_right (d_right (dc))));
      d_append_string (dpi, ") : (");
      d_print_comp (dpi, d_right (d_right (d_right (dc))));
      d_append_char (dpi, ')');
      return;

    case DEMANGLE_COMPONENT_TRINARY_ARG1:
    case DEMANGLE_COMPONENT_TRINARY_ARG2:
      /* We should only see these are part of DEMANGLE_COMPONENT_TRINARY.  */
      d_print_error (dpi);
      return;

    case DEMANGLE_COMPONENT_LITERAL:
    case DEMANGLE_COMPONENT_LITERAL_NEG:
      {
	enum d_builtin_type_print tp;

	/* For some builtin types, produce simpler output.  */
	tp = D_PRINT_DEFAULT;
	if (d_left (dc)->type == DEMANGLE_COMPONENT_BUILTIN_TYPE)
	  {
	    tp = d_left (dc)->u.s_builtin.type->print;
	    switch (tp)
	      {
	      case D_PRINT_INT:
	      case D_PRINT_UNSIGNED:
	      case D_PRINT_LONG:
	      case D_PRINT_UNSIGNED_LONG:
	      case D_PRINT_LONG_LONG:
	      case D_PRINT_UNSIGNED_LONG_LONG:
		if (d_right (dc)->type == DEMANGLE_COMPONENT_NAME)
		  {
		    if (dc->type == DEMANGLE_COMPONENT_LITERAL_NEG)
		      d_append_char (dpi, '-');
		    d_print_comp (dpi, d_right (dc));
		    switch (tp)
		      {
		      default:
			break;
		      case D_PRINT_UNSIGNED:
			d_append_char (dpi, 'u');
			break;
		      case D_PRINT_LONG:
			d_append_char (dpi, 'l');
			break;
		      case D_PRINT_UNSIGNED_LONG:
			d_append_string (dpi, "ul");
			break;
		      case D_PRINT_LONG_LONG:
			d_append_string (dpi, "ll");
			break;
		      case D_PRINT_UNSIGNED_LONG_LONG:
			d_append_string (dpi, "ull");
			break;
		      }
		    return;
		  }
		break;

	      case D_PRINT_BOOL:
		if (d_right (dc)->type == DEMANGLE_COMPONENT_NAME
		    && d_right (dc)->u.s_name.len == 1
		    && dc->type == DEMANGLE_COMPONENT_LITERAL)
		  {
		    switch (d_right (dc)->u.s_name.s[0])
		      {
		      case '0':
			d_append_string (dpi, "false");
			return;
		      case '1':
			d_append_string (dpi, "true");
			return;
		      default:
			break;
		      }
		  }
		break;

	      default:
		break;
	      }
	  }

	d_append_char (dpi, '(');
	d_print_comp (dpi, d_left (dc));
	d_append_char (dpi, ')');
	if (dc->type == DEMANGLE_COMPONENT_LITERAL_NEG)
	  d_append_char (dpi, '-');
	if (tp == D_PRINT_FLOAT)
	  d_append_char (dpi, '[');
	d_print_comp (dpi, d_right (dc));
	if (tp == D_PRINT_FLOAT)
	  d_append_char (dpi, ']');
      }
      return;

    default:
      d_print_error (dpi);
      return;
    }
}