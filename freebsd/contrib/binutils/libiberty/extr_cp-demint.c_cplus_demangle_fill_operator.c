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
struct TYPE_4__ {TYPE_3__* op; } ;
struct TYPE_5__ {TYPE_1__ s_operator; } ;
struct demangle_component {TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int len; int args; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEMANGLE_COMPONENT_OPERATOR ; 
 TYPE_3__* cplus_demangle_operators ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

int
cplus_demangle_fill_operator (struct demangle_component *p,
                              const char *opname, int args)
{
  int len;
  unsigned int i;

  if (p == NULL || opname == NULL)
    return 0;
  len = strlen (opname);
  for (i = 0; cplus_demangle_operators[i].name != NULL; ++i)
    {
      if (len == cplus_demangle_operators[i].len
	  && args == cplus_demangle_operators[i].args
	  && strcmp (opname, cplus_demangle_operators[i].name) == 0)
	{
	  p->type = DEMANGLE_COMPONENT_OPERATOR;
	  p->u.s_operator.op = &cplus_demangle_operators[i];
	  return 1;
	}
    }
  return 0;
}