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
struct block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_SYMBOL_NAME (struct symbol*) ; 
 scalar_t__ mangled_ordered_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sort_choices (struct symbol *syms[], struct block *blocks[], int nsyms)
{
  int i, j;
  for (i = 1; i < nsyms; i += 1)
    {
      struct symbol *sym = syms[i];
      struct block *block = blocks[i];
      int j;

      for (j = i - 1; j >= 0; j -= 1)
	{
	  if (mangled_ordered_before (DEPRECATED_SYMBOL_NAME (syms[j]),
				      DEPRECATED_SYMBOL_NAME (sym)))
	    break;
	  syms[j + 1] = syms[j];
	  blocks[j + 1] = blocks[j];
	}
      syms[j + 1] = sym;
      blocks[j + 1] = block;
    }
}