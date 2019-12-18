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
typedef  int /*<<< orphan*/  type_p ;
struct nested_ptr_data {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__* options_p ;
typedef  enum gc_used_enum { ____Placeholder_gc_used_enum } gc_used_enum ;
struct TYPE_3__ {scalar_t__ info; int /*<<< orphan*/  name; struct TYPE_3__* next; } ;

/* Variables and functions */
 int GC_POINTED_TO ; 
 int /*<<< orphan*/  set_gc_used_type (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
process_gc_options (options_p opt, enum gc_used_enum level, int *maybe_undef,
		    int *pass_param, int *length, type_p *nested_ptr)
{
  options_p o;
  for (o = opt; o; o = o->next)
    if (strcmp (o->name, "ptr_alias") == 0 && level == GC_POINTED_TO)
      set_gc_used_type ((type_p) o->info, GC_POINTED_TO, NULL);
    else if (strcmp (o->name, "maybe_undef") == 0)
      *maybe_undef = 1;
    else if (strcmp (o->name, "use_params") == 0)
      *pass_param = 1;
    else if (strcmp (o->name, "length") == 0)
      *length = 1;
    else if (strcmp (o->name, "nested_ptr") == 0)
      *nested_ptr = ((const struct nested_ptr_data *) o->info)->type;
}