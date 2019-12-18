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
 scalar_t__ DEPRECATED_STREQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DEPRECATED_SYMBOL_NAME (struct symbol*) ; 
 scalar_t__ LOC_STATIC ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_TYPE (struct symbol*) ; 
 scalar_t__ SYMBOL_VALUE_ADDRESS (struct symbol*) ; 
 scalar_t__ is_nondebugging_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
remove_extra_symbols (struct symbol **syms, struct block **blocks, int nsyms)
{
  int i, j;

  i = 0;
  while (i < nsyms)
    {
      if (DEPRECATED_SYMBOL_NAME (syms[i]) != NULL
	  && SYMBOL_CLASS (syms[i]) == LOC_STATIC
	  && is_nondebugging_type (SYMBOL_TYPE (syms[i])))
	{
	  for (j = 0; j < nsyms; j += 1)
	    {
	      if (i != j
		  && DEPRECATED_SYMBOL_NAME (syms[j]) != NULL
		  && DEPRECATED_STREQ (DEPRECATED_SYMBOL_NAME (syms[i]), DEPRECATED_SYMBOL_NAME (syms[j]))
		  && SYMBOL_CLASS (syms[i]) == SYMBOL_CLASS (syms[j])
		  && SYMBOL_VALUE_ADDRESS (syms[i])
		  == SYMBOL_VALUE_ADDRESS (syms[j]))
		{
		  int k;
		  for (k = i + 1; k < nsyms; k += 1)
		    {
		      syms[k - 1] = syms[k];
		      blocks[k - 1] = blocks[k];
		    }
		  nsyms -= 1;
		  goto NextSymbol;
		}
	    }
	}
      i += 1;
    NextSymbol:
      ;
    }
  return nsyms;
}