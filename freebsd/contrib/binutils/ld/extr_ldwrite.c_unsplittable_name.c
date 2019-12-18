#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 scalar_t__ CONST_STRNEQ (char const*,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmp (char const*,char*) ; 
 unsigned int strlen (char const*) ; 

__attribute__((used)) static bfd_boolean
unsplittable_name (const char *name)
{
  if (CONST_STRNEQ (name, ".stab"))
    {
      /* There are several stab like string sections. We pattern match on
	 ".stab...str"  */
      unsigned len = strlen (name);
      if (strcmp (&name[len-3], "str") == 0)
	return TRUE;
    }
  else if (strcmp (name, "$GDB_STRINGS$") == 0)
    return TRUE;
  return FALSE;
}