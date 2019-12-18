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
struct section_name_struct {struct section_name_struct* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 struct section_name_struct* xmalloc (int) ; 

__attribute__((used)) static struct section_name_struct **
lookup (const char *name, struct section_name_struct **list)
{
  struct section_name_struct **ptr = list;

  while (*ptr)
    {
      if (strcmp (name, (*ptr)->name) == 0)
	/* If this is a match, delete it, we only keep the last instance
	   of any name.  */
	*ptr = (*ptr)->next;
      else
	ptr = &((*ptr)->next);
    }

  *ptr = xmalloc (sizeof (struct section_name_struct));
  return ptr;
}