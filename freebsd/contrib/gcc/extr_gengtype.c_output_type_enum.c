#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* type_p ;
typedef  int /*<<< orphan*/  outf_p ;
struct TYPE_8__ {int /*<<< orphan*/ * file; } ;
struct TYPE_9__ {TYPE_1__ line; } ;
struct TYPE_10__ {TYPE_2__ s; } ;
struct TYPE_11__ {scalar_t__ kind; TYPE_3__ u; } ;

/* Variables and functions */
 scalar_t__ TYPE_PARAM_STRUCT ; 
 scalar_t__ UNION_OR_STRUCT_P (TYPE_4__*) ; 
 int /*<<< orphan*/  oprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  output_mangled_typename (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void
output_type_enum (outf_p of, type_p s)
{
  if (s->kind == TYPE_PARAM_STRUCT && s->u.s.line.file != NULL)
    {
      oprintf (of, ", gt_e_");
      output_mangled_typename (of, s);
    }
  else if (UNION_OR_STRUCT_P (s) && s->u.s.line.file != NULL)
    {
      oprintf (of, ", gt_ggc_e_");
      output_mangled_typename (of, s);
    }
  else
    oprintf (of, ", gt_types_enum_last");
}