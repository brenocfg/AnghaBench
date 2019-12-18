#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mapping {scalar_t__* name; struct map_value* values; TYPE_1__* group; } ;
struct map_value {int number; struct map_value* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  attrs; } ;

/* Variables and functions */
 scalar_t__ htab_find (int /*<<< orphan*/ ,char const**) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strncmp (char const*,scalar_t__*,int) ; 

__attribute__((used)) static struct map_value *
map_attr_string (const char *p, struct mapping *macro, int value)
{
  const char *attr;
  struct mapping *m;
  struct map_value *v;

  /* If there's a "macro:" prefix, check whether the macro name matches.
     Set ATTR to the start of the attribute name.  */
  attr = strchr (p, ':');
  if (attr == 0)
    attr = p;
  else
    {
      if (strncmp (p, macro->name, attr - p) != 0
	  || macro->name[attr - p] != 0)
	return 0;
      attr++;
    }

  /* Find the attribute specification.  */
  m = (struct mapping *) htab_find (macro->group->attrs, &attr);
  if (m == 0)
    return 0;

  /* Find the attribute value for VALUE.  */
  for (v = m->values; v != 0; v = v->next)
    if (v->number == value)
      break;

  return v;
}