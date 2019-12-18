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
struct TYPE_3__ {int kind; struct demangle_component* name; } ;
struct TYPE_4__ {TYPE_1__ s_dtor; } ;
struct demangle_component {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  enum gnu_v3_dtor_kinds { ____Placeholder_gnu_v3_dtor_kinds } gnu_v3_dtor_kinds ;

/* Variables and functions */
 int /*<<< orphan*/  DEMANGLE_COMPONENT_DTOR ; 
 int gnu_v3_base_object_dtor ; 
 int gnu_v3_deleting_dtor ; 

int
cplus_demangle_fill_dtor (struct demangle_component *p,
                          enum gnu_v3_dtor_kinds kind,
                          struct demangle_component *name)
{
  if (p == NULL
      || name == NULL
      || (kind < gnu_v3_deleting_dtor
	  && kind > gnu_v3_base_object_dtor))
    return 0;
  p->type = DEMANGLE_COMPONENT_DTOR;
  p->u.s_dtor.kind = kind;
  p->u.s_dtor.name = name;
  return 1;
}