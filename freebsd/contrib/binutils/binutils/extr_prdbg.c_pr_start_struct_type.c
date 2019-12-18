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
struct TYPE_2__ {int /*<<< orphan*/  visibility; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_VISIBILITY_PUBLIC ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  append_type (struct pr_handle*,char const*) ; 
 scalar_t__ indent_type (struct pr_handle*) ; 
 int /*<<< orphan*/  push_type (struct pr_handle*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
pr_start_struct_type (void *p, const char *tag, unsigned int id,
		      bfd_boolean structp, unsigned int size)
{
  struct pr_handle *info = (struct pr_handle *) p;

  info->indent += 2;

  if (! push_type (info, structp ? "struct " : "union "))
    return FALSE;
  if (tag != NULL)
    {
      if (! append_type (info, tag))
	return FALSE;
    }
  else
    {
      char idbuf[20];

      sprintf (idbuf, "%%anon%u", id);
      if (! append_type (info, idbuf))
	return FALSE;
    }

  if (! append_type (info, " {"))
    return FALSE;
  if (size != 0 || tag != NULL)
    {
      char ab[30];

      if (! append_type (info, " /*"))
	return FALSE;

      if (size != 0)
	{
	  sprintf (ab, " size %u", size);
	  if (! append_type (info, ab))
	    return FALSE;
	}
      if (tag != NULL)
	{
	  sprintf (ab, " id %u", id);
	  if (! append_type (info, ab))
	    return FALSE;
	}
      if (! append_type (info, " */"))
	return FALSE;
    }
  if (! append_type (info, "\n"))
    return FALSE;

  info->stack->visibility = DEBUG_VISIBILITY_PUBLIC;

  return indent_type (info);
}