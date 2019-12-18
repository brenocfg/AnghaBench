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
struct group_reloc_table_entry {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct group_reloc_table_entry*) ; 
 int FAIL ; 
 int SUCCESS ; 
 struct group_reloc_table_entry* group_reloc_table ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncasecmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
find_group_reloc_table_entry (char **str, struct group_reloc_table_entry **out)
{
  unsigned int i;
  for (i = 0; i < ARRAY_SIZE (group_reloc_table); i++)
    {
      int length = strlen (group_reloc_table[i].name);

      if (strncasecmp (group_reloc_table[i].name, *str, length) == 0 &&
          (*str)[length] == ':')
        {
          *out = &group_reloc_table[i];
          *str += (length + 1);
          return SUCCESS;
        }
    }

  return FAIL;
}