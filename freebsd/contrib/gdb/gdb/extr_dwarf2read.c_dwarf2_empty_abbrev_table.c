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
struct abbrev_info {struct abbrev_info* attrs; struct abbrev_info* next; } ;

/* Variables and functions */
 int ABBREV_HASH_SIZE ; 
 int /*<<< orphan*/  xfree (struct abbrev_info*) ; 

__attribute__((used)) static void
dwarf2_empty_abbrev_table (void *ptr_to_abbrevs_table)
{
  int i;
  struct abbrev_info *abbrev, *next;
  struct abbrev_info **abbrevs;

  abbrevs = (struct abbrev_info **)ptr_to_abbrevs_table;

  for (i = 0; i < ABBREV_HASH_SIZE; ++i)
    {
      next = NULL;
      abbrev = abbrevs[i];
      while (abbrev)
	{
	  next = abbrev->next;
	  xfree (abbrev->attrs);
	  xfree (abbrev);
	  abbrev = next;
	}
      abbrevs[i] = NULL;
    }
}