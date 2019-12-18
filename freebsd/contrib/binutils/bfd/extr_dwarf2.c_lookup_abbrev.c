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
struct abbrev_info {unsigned int number; struct abbrev_info* next; } ;

/* Variables and functions */
 unsigned int ABBREV_HASH_SIZE ; 

__attribute__((used)) static struct abbrev_info *
lookup_abbrev (unsigned int number, struct abbrev_info **abbrevs)
{
  unsigned int hash_number;
  struct abbrev_info *abbrev;

  hash_number = number % ABBREV_HASH_SIZE;
  abbrev = abbrevs[hash_number];

  while (abbrev)
    {
      if (abbrev->number == number)
	return abbrev;
      else
	abbrev = abbrev->next;
    }

  return NULL;
}