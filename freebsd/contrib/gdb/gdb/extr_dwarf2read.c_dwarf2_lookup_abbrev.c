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
struct comp_unit_head {struct abbrev_info** dwarf2_abbrevs; } ;
struct dwarf2_cu {struct comp_unit_head header; } ;
struct abbrev_info {unsigned int number; struct abbrev_info* next; } ;

/* Variables and functions */
 unsigned int ABBREV_HASH_SIZE ; 

__attribute__((used)) static struct abbrev_info *
dwarf2_lookup_abbrev (unsigned int number, struct dwarf2_cu *cu)
{
  struct comp_unit_head *cu_header = &cu->header;
  unsigned int hash_number;
  struct abbrev_info *abbrev;

  hash_number = number % ABBREV_HASH_SIZE;
  abbrev = cu_header->dwarf2_abbrevs[hash_number];

  while (abbrev)
    {
      if (abbrev->number == number)
	return abbrev;
      else
	abbrev = abbrev->next;
    }
  return NULL;
}