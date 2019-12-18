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
typedef  struct symbol block ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GROW_VECT (struct symbol**,size_t,int) ; 
 int /*<<< orphan*/ * SYMBOL_TYPE (struct symbol*) ; 
 struct symbol** defn_blocks ; 
 struct symbol** defn_symbols ; 
 size_t defn_vector_size ; 
 scalar_t__ lesseq_defined_than (struct symbol*,struct symbol*) ; 
 int ndefns ; 

__attribute__((used)) static void
add_defn_to_vec (struct symbol *sym, struct block *block)
{
  int i;
  size_t tmp;

  if (SYMBOL_TYPE (sym) != NULL)
    CHECK_TYPEDEF (SYMBOL_TYPE (sym));
  for (i = 0; i < ndefns; i += 1)
    {
      if (lesseq_defined_than (sym, defn_symbols[i]))
	return;
      else if (lesseq_defined_than (defn_symbols[i], sym))
	{
	  defn_symbols[i] = sym;
	  defn_blocks[i] = block;
	  return;
	}
    }

  tmp = defn_vector_size;
  GROW_VECT (defn_symbols, tmp, ndefns + 2);
  GROW_VECT (defn_blocks, defn_vector_size, ndefns + 2);

  defn_symbols[ndefns] = sym;
  defn_blocks[ndefns] = block;
  ndefns += 1;
}