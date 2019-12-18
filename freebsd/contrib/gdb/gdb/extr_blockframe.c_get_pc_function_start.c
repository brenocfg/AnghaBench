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
struct minimal_symbol {int dummy; } ;
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_START (struct block*) ; 
 struct block* SYMBOL_BLOCK_VALUE (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 struct block* block_for_pc (int /*<<< orphan*/ ) ; 
 struct symbol* block_function (struct block*) ; 
 scalar_t__ find_pc_section (int /*<<< orphan*/ ) ; 
 struct minimal_symbol* lookup_minimal_symbol_by_pc (int /*<<< orphan*/ ) ; 

CORE_ADDR
get_pc_function_start (CORE_ADDR pc)
{
  struct block *bl;
  struct minimal_symbol *msymbol;

  bl = block_for_pc (pc);
  if (bl)
    {
      struct symbol *symbol = block_function (bl);

      if (symbol)
	{
	  bl = SYMBOL_BLOCK_VALUE (symbol);
	  return BLOCK_START (bl);
	}
    }

  msymbol = lookup_minimal_symbol_by_pc (pc);
  if (msymbol)
    {
      CORE_ADDR fstart = SYMBOL_VALUE_ADDRESS (msymbol);

      if (find_pc_section (fstart))
	return fstart;
    }

  return 0;
}