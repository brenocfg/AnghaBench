#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* type_p ;
struct walk_type_data {int /*<<< orphan*/  val; int /*<<< orphan*/  indent; int /*<<< orphan*/  of; int /*<<< orphan*/ * prev_val; } ;
struct TYPE_3__ {int kind; } ;

/* Variables and functions */
#define  TYPE_LANG_STRUCT 134 
#define  TYPE_PARAM_STRUCT 133 
#define  TYPE_POINTER 132 
#define  TYPE_SCALAR 131 
#define  TYPE_STRING 130 
#define  TYPE_STRUCT 129 
#define  TYPE_UNION 128 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  oprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
write_types_local_process_field (type_p f, const struct walk_type_data *d)
{
  switch (f->kind)
    {
    case TYPE_POINTER:
    case TYPE_STRUCT:
    case TYPE_UNION:
    case TYPE_LANG_STRUCT:
    case TYPE_PARAM_STRUCT:
    case TYPE_STRING:
      oprintf (d->of, "%*sif ((void *)(%s) == this_obj)\n", d->indent, "",
	       d->prev_val[3]);
      oprintf (d->of, "%*s  op (&(%s), cookie);\n", d->indent, "", d->val);
      break;

    case TYPE_SCALAR:
      break;

    default:
      gcc_unreachable ();
    }
}