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
struct pr_handle {int indent; TYPE_1__* stack; } ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_2__ {char* flavor; int /*<<< orphan*/  visibility; scalar_t__ num_parents; int /*<<< orphan*/ * parents; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_VISIBILITY_PRIVATE ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  append_type (struct pr_handle*,char*) ; 
 char* pop_type (struct pr_handle*) ; 
 int /*<<< orphan*/  push_type (struct pr_handle*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
tg_start_class_type (void *p, const char *tag, unsigned int id,
		     bfd_boolean structp, unsigned int size,
		     bfd_boolean vptr, bfd_boolean ownvptr)
{
  struct pr_handle *info = (struct pr_handle *) p;
  char *tv = NULL;
  const char *name;

  info->indent += 2;

  if (vptr && ! ownvptr)
    {
      tv = pop_type (info);
      if (tv == NULL)
	return FALSE;
    }

  if (tag != NULL)
    name = tag;
  else
    {
      char idbuf[20];

      sprintf (idbuf, "%%anon%u", id);
      name = idbuf;
    }

  if (! push_type (info, name))
    return FALSE;

  info->stack->flavor = structp ? "class" : "union class";
  info->stack->parents = NULL;
  info->stack->num_parents = 0;

  if (size != 0 || vptr || ownvptr || tag != NULL)
    {
      if (vptr)
	{
	  if (! append_type (info, " vtable "))
	    return FALSE;
	  if (ownvptr)
	    {
	      if (! append_type (info, "self "))
		return FALSE;
	    }
	  else
	    {
	      if (! append_type (info, tv)
		  || ! append_type (info, " "))
		return FALSE;
	    }
	}
    }

  info->stack->visibility = DEBUG_VISIBILITY_PRIVATE;

  return TRUE;
}