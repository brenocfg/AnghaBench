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
struct linetable_entry {scalar_t__ pc; int line; } ;

/* Variables and functions */

__attribute__((used)) static int
compare_line_numbers (const void *ln1p, const void *ln2p)
{
  struct linetable_entry *ln1 = (struct linetable_entry *) ln1p;
  struct linetable_entry *ln2 = (struct linetable_entry *) ln2p;

  /* Note: this code does not assume that CORE_ADDRs can fit in ints.
     Please keep it that way.  */
  if (ln1->pc < ln2->pc)
    return -1;

  if (ln1->pc > ln2->pc)
    return 1;

  /* If pc equal, sort by line.  I'm not sure whether this is optimum
     behavior (see comment at struct linetable in symtab.h).  */
  return ln1->line - ln2->line;
}