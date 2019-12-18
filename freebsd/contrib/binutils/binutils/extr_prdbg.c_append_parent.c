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
struct pr_handle {TYPE_1__* stack; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {char* parents; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 unsigned int strlen (char const*) ; 
 scalar_t__ xrealloc (char*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
append_parent (struct pr_handle *info, const char *s)
{
  unsigned int len;

  if (s == NULL)
    return FALSE;

  assert (info->stack != NULL);

  len = info->stack->parents ? strlen (info->stack->parents) : 0;
  info->stack->parents = (char *) xrealloc (info->stack->parents,
					    len + strlen (s) + 1);
  strcpy (info->stack->parents + len, s);

  return TRUE;
}