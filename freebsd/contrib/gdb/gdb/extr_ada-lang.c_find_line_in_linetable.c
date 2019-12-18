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
struct symbol {int dummy; } ;
struct linetable_entry {scalar_t__ pc; int line; } ;
struct linetable {int nitems; struct linetable_entry* item; } ;

/* Variables and functions */
 scalar_t__ BLOCK_END (int /*<<< orphan*/ ) ; 
 scalar_t__ BLOCK_START (int /*<<< orphan*/ ) ; 
 scalar_t__ LOC_BLOCK ; 
 int /*<<< orphan*/  SYMBOL_BLOCK_VALUE (struct symbol*) ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 

__attribute__((used)) static int
find_line_in_linetable (struct linetable *linetable, int line_num,
			struct symbol **symbols, int nsyms, int *exactp)
{
  int i, len, best_index, best;

  if (line_num <= 0 || linetable == NULL)
    return -1;

  len = linetable->nitems;
  for (i = 0, best_index = -1, best = 0; i < len; i += 1)
    {
      int k;
      struct linetable_entry *item = &(linetable->item[i]);

      for (k = 0; k < nsyms; k += 1)
	{
	  if (symbols[k] != NULL && SYMBOL_CLASS (symbols[k]) == LOC_BLOCK
	      && item->pc >= BLOCK_START (SYMBOL_BLOCK_VALUE (symbols[k]))
	      && item->pc < BLOCK_END (SYMBOL_BLOCK_VALUE (symbols[k])))
	    goto candidate;
	}
      continue;

    candidate:

      if (item->line == line_num)
	{
	  *exactp = 1;
	  return i;
	}

      if (item->line > line_num && (best == 0 || item->line < best))
	{
	  best = item->line;
	  best_index = i;
	}
    }

  *exactp = 0;
  return best_index;
}