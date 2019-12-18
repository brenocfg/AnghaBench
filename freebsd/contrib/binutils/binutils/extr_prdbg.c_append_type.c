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
struct TYPE_2__ {char const* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char const*,char const*) ; 
 unsigned int strlen (char const*) ; 
 scalar_t__ xrealloc (char*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
append_type (struct pr_handle *info, const char *s)
{
  unsigned int len;

  if (s == NULL)
    return FALSE;

  assert (info->stack != NULL);

  len = strlen (info->stack->type);
  info->stack->type = (char *) xrealloc (info->stack->type,
					 len + strlen (s) + 1);
  strcpy (info->stack->type + len, s);

  return TRUE;
}