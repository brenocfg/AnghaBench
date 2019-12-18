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
struct TYPE_4__ {TYPE_3__* type; } ;
struct TYPE_5__ {TYPE_1__ s_builtin; } ;
struct demangle_component {TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMANGLE_COMPONENT_BUILTIN_TYPE ; 
 unsigned int D_BUILTIN_TYPE_COUNT ; 
 TYPE_3__* cplus_demangle_builtin_types ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

int
cplus_demangle_fill_builtin_type (struct demangle_component *p,
                                  const char *type_name)
{
  int len;
  unsigned int i;

  if (p == NULL || type_name == NULL)
    return 0;
  len = strlen (type_name);
  for (i = 0; i < D_BUILTIN_TYPE_COUNT; ++i)
    {
      if (len == cplus_demangle_builtin_types[i].len
	  && strcmp (type_name, cplus_demangle_builtin_types[i].name) == 0)
	{
	  p->type = DEMANGLE_COMPONENT_BUILTIN_TYPE;
	  p->u.s_builtin.type = &cplus_demangle_builtin_types[i];
	  return 1;
	}
    }
  return 0;
}