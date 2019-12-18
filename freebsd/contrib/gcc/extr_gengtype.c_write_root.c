#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* type_p ;
struct fileloc {int dummy; } ;
typedef  TYPE_5__* pair_p ;
typedef  int /*<<< orphan*/  outf_p ;
typedef  TYPE_6__* options_p ;
struct TYPE_16__ {char const* name; char* info; struct TYPE_16__* next; } ;
struct TYPE_15__ {int /*<<< orphan*/  name; TYPE_4__* type; TYPE_6__* opt; struct TYPE_15__* next; } ;
struct TYPE_12__ {int /*<<< orphan*/  tag; TYPE_5__* fields; } ;
struct TYPE_11__ {TYPE_4__* p; int /*<<< orphan*/ * len; } ;
struct TYPE_13__ {TYPE_2__ s; TYPE_4__* p; TYPE_1__ a; } ;
struct TYPE_14__ {int kind; TYPE_3__ u; } ;

/* Variables and functions */
#define  TYPE_ARRAY 132 
 int const TYPE_PARAM_STRUCT ; 
#define  TYPE_POINTER 131 
#define  TYPE_SCALAR 130 
#define  TYPE_STRING 129 
#define  TYPE_STRUCT 128 
 int TYPE_UNION ; 
 int /*<<< orphan*/  UNION_OR_STRUCT_P (TYPE_4__*) ; 
 int /*<<< orphan*/  error_at_line (struct fileloc*,char*,char const*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  oprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  output_mangled_typename (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 char* xasprintf (char*,char const*,...) ; 

__attribute__((used)) static void
write_root (outf_p f, pair_p v, type_p type, const char *name, int has_length,
	    struct fileloc *line, const char *if_marked)
{
  switch (type->kind)
    {
    case TYPE_STRUCT:
      {
	pair_p fld;
	for (fld = type->u.s.fields; fld; fld = fld->next)
	  {
	    int skip_p = 0;
	    const char *desc = NULL;
	    options_p o;

	    for (o = fld->opt; o; o = o->next)
	      if (strcmp (o->name, "skip") == 0)
		skip_p = 1;
	      else if (strcmp (o->name, "desc") == 0)
		desc = o->info;
	      else
		error_at_line (line,
		       "field `%s' of global `%s' has unknown option `%s'",
			       fld->name, name, o->name);

	    if (skip_p)
	      continue;
	    else if (desc && fld->type->kind == TYPE_UNION)
	      {
		pair_p validf = NULL;
		pair_p ufld;

		for (ufld = fld->type->u.s.fields; ufld; ufld = ufld->next)
		  {
		    const char *tag = NULL;
		    options_p oo;

		    for (oo = ufld->opt; oo; oo = oo->next)
		      if (strcmp (oo->name, "tag") == 0)
			tag = oo->info;
		    if (tag == NULL || strcmp (tag, desc) != 0)
		      continue;
		    if (validf != NULL)
		      error_at_line (line,
			   "both `%s.%s.%s' and `%s.%s.%s' have tag `%s'",
				     name, fld->name, validf->name,
				     name, fld->name, ufld->name,
				     tag);
		    validf = ufld;
		  }
		if (validf != NULL)
		  {
		    char *newname;
		    newname = xasprintf ("%s.%s.%s",
					 name, fld->name, validf->name);
		    write_root (f, v, validf->type, newname, 0, line,
				if_marked);
		    free (newname);
		  }
	      }
	    else if (desc)
	      error_at_line (line,
		     "global `%s.%s' has `desc' option but is not union",
			     name, fld->name);
	    else
	      {
		char *newname;
		newname = xasprintf ("%s.%s", name, fld->name);
		write_root (f, v, fld->type, newname, 0, line, if_marked);
		free (newname);
	      }
	  }
      }
      break;

    case TYPE_ARRAY:
      {
	char *newname;
	newname = xasprintf ("%s[0]", name);
	write_root (f, v, type->u.a.p, newname, has_length, line, if_marked);
	free (newname);
      }
      break;

    case TYPE_POINTER:
      {
	type_p ap, tp;

	oprintf (f, "  {\n");
	oprintf (f, "    &%s,\n", name);
	oprintf (f, "    1");

	for (ap = v->type; ap->kind == TYPE_ARRAY; ap = ap->u.a.p)
	  if (ap->u.a.len[0])
	    oprintf (f, " * (%s)", ap->u.a.len);
	  else if (ap == v->type)
	    oprintf (f, " * ARRAY_SIZE (%s)", v->name);
	oprintf (f, ",\n");
	oprintf (f, "    sizeof (%s", v->name);
	for (ap = v->type; ap->kind == TYPE_ARRAY; ap = ap->u.a.p)
	  oprintf (f, "[0]");
	oprintf (f, "),\n");

	tp = type->u.p;

	if (! has_length && UNION_OR_STRUCT_P (tp))
	  {
	    oprintf (f, "    &gt_ggc_mx_%s,\n", tp->u.s.tag);
	    oprintf (f, "    &gt_pch_nx_%s", tp->u.s.tag);
	  }
	else if (! has_length && tp->kind == TYPE_PARAM_STRUCT)
	  {
	    oprintf (f, "    &gt_ggc_m_");
	    output_mangled_typename (f, tp);
	    oprintf (f, ",\n    &gt_pch_n_");
	    output_mangled_typename (f, tp);
	  }
	else if (has_length
		 && (tp->kind == TYPE_POINTER || UNION_OR_STRUCT_P (tp)))
	  {
	    oprintf (f, "    &gt_ggc_ma_%s,\n", name);
	    oprintf (f, "    &gt_pch_na_%s", name);
	  }
	else
	  {
	    error_at_line (line,
			   "global `%s' is pointer to unimplemented type",
			   name);
	  }
	if (if_marked)
	  oprintf (f, ",\n    &%s", if_marked);
	oprintf (f, "\n  },\n");
      }
      break;

    case TYPE_STRING:
      {
	oprintf (f, "  {\n");
	oprintf (f, "    &%s,\n", name);
	oprintf (f, "    1, \n");
	oprintf (f, "    sizeof (%s),\n", v->name);
	oprintf (f, "    &gt_ggc_m_S,\n");
	oprintf (f, "    (gt_pointer_walker) &gt_pch_n_S\n");
	oprintf (f, "  },\n");
      }
      break;

    case TYPE_SCALAR:
      break;

    default:
      error_at_line (line,
		     "global `%s' is unimplemented type",
		     name);
    }
}