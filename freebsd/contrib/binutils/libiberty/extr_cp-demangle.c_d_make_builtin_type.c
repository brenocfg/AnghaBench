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
struct TYPE_3__ {struct demangle_builtin_type_info const* type; } ;
struct TYPE_4__ {TYPE_1__ s_builtin; } ;
struct demangle_component {TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct demangle_builtin_type_info {int dummy; } ;
struct d_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMANGLE_COMPONENT_BUILTIN_TYPE ; 
 struct demangle_component* d_make_empty (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_make_builtin_type (struct d_info *di,
                     const struct demangle_builtin_type_info *type)
{
  struct demangle_component *p;

  if (type == NULL)
    return NULL;
  p = d_make_empty (di);
  if (p != NULL)
    {
      p->type = DEMANGLE_COMPONENT_BUILTIN_TYPE;
      p->u.s_builtin.type = type;
    }
  return p;
}