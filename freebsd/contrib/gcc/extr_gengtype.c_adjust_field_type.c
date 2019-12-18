#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_7__* type_p ;
typedef  TYPE_8__* options_p ;
struct TYPE_34__ {char const* name; char* info; struct TYPE_34__* next; } ;
struct TYPE_31__ {int /*<<< orphan*/  len; TYPE_4__* p; } ;
struct TYPE_32__ {char const* sc; TYPE_5__ a; TYPE_7__* p; } ;
struct TYPE_33__ {scalar_t__ kind; TYPE_6__ u; } ;
struct TYPE_29__ {TYPE_2__* p; } ;
struct TYPE_30__ {scalar_t__ kind; TYPE_3__ u; } ;
struct TYPE_27__ {char const* sc; } ;
struct TYPE_28__ {scalar_t__ kind; TYPE_1__ u; } ;

/* Variables and functions */
 scalar_t__ ISDIGIT (char const) ; 
 int NUM_PARAM ; 
 scalar_t__ TYPE_ARRAY ; 
 scalar_t__ TYPE_POINTER ; 
 scalar_t__ TYPE_SCALAR ; 
 int /*<<< orphan*/  UNION_OR_STRUCT_P (TYPE_7__*) ; 
 TYPE_7__* adjust_field_rtx_def (TYPE_7__*,TYPE_8__*) ; 
 TYPE_7__* adjust_field_tree_exp (TYPE_7__*,TYPE_8__*) ; 
 TYPE_7__* create_array (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* create_pointer (TYPE_7__*) ; 
 int /*<<< orphan*/  error_at_line (int /*<<< orphan*/ *,char*,char const*) ; 
 TYPE_7__* find_param_structure (TYPE_7__*,TYPE_7__**) ; 
 int /*<<< orphan*/  lexer_line ; 
 scalar_t__ strcmp (char const*,char*) ; 
 TYPE_7__ string_type ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

type_p
adjust_field_type (type_p t, options_p opt)
{
  int length_p = 0;
  const int pointer_p = t->kind == TYPE_POINTER;
  type_p params[NUM_PARAM];
  int params_p = 0;
  int i;

  for (i = 0; i < NUM_PARAM; i++)
    params[i] = NULL;

  for (; opt; opt = opt->next)
    if (strcmp (opt->name, "length") == 0)
      length_p = 1;
    else if (strcmp (opt->name, "param_is") == 0
	     || (strncmp (opt->name, "param", 5) == 0
		 && ISDIGIT (opt->name[5])
		 && strcmp (opt->name + 6, "_is") == 0))
      {
	int num = ISDIGIT (opt->name[5]) ? opt->name[5] - '0' : 0;

	if (! UNION_OR_STRUCT_P (t)
	    && (t->kind != TYPE_POINTER || ! UNION_OR_STRUCT_P (t->u.p)))
	  {
	    error_at_line (&lexer_line,
   "option `%s' may only be applied to structures or structure pointers",
			   opt->name);
	    return t;
	  }

	params_p = 1;
	if (params[num] != NULL)
	  error_at_line (&lexer_line, "duplicate `%s' option", opt->name);
	if (! ISDIGIT (opt->name[5]))
	  params[num] = create_pointer ((type_p) opt->info);
	else
	  params[num] = (type_p) opt->info;
      }
    else if (strcmp (opt->name, "special") == 0)
      {
	const char *special_name = opt->info;
	if (strcmp (special_name, "tree_exp") == 0)
	  t = adjust_field_tree_exp (t, opt);
	else if (strcmp (special_name, "rtx_def") == 0)
	  t = adjust_field_rtx_def (t, opt);
	else
	  error_at_line (&lexer_line, "unknown special `%s'", special_name);
      }

  if (params_p)
    {
      type_p realt;

      if (pointer_p)
	t = t->u.p;
      realt = find_param_structure (t, params);
      t = pointer_p ? create_pointer (realt) : realt;
    }

  if (! length_p
      && pointer_p
      && t->u.p->kind == TYPE_SCALAR
      && (strcmp (t->u.p->u.sc, "char") == 0
	  || strcmp (t->u.p->u.sc, "unsigned char") == 0))
    return &string_type;
  if (t->kind == TYPE_ARRAY && t->u.a.p->kind == TYPE_POINTER
      && t->u.a.p->u.p->kind == TYPE_SCALAR
      && (strcmp (t->u.a.p->u.p->u.sc, "char") == 0
	  || strcmp (t->u.a.p->u.p->u.sc, "unsigned char") == 0))
    return create_array (&string_type, t->u.a.len);

  return t;
}