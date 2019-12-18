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
struct table_elt {struct table_elt* next_same_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_HARD_REG_SET (int /*<<< orphan*/ ) ; 
 int HASH_SIZE ; 
 int /*<<< orphan*/  cse_reg_info_timestamp ; 
 struct table_elt* free_element_chain ; 
 int /*<<< orphan*/  hard_regs_in_table ; 
 scalar_t__ next_qty ; 
 scalar_t__ prev_insn ; 
 scalar_t__ prev_insn_cc0 ; 
 struct table_elt** table ; 
 scalar_t__ table_size ; 

__attribute__((used)) static void
new_basic_block (void)
{
  int i;

  next_qty = 0;

  /* Invalidate cse_reg_info_table.  */
  cse_reg_info_timestamp++;

  /* Clear out hash table state for this pass.  */
  CLEAR_HARD_REG_SET (hard_regs_in_table);

  /* The per-quantity values used to be initialized here, but it is
     much faster to initialize each as it is made in `make_new_qty'.  */

  for (i = 0; i < HASH_SIZE; i++)
    {
      struct table_elt *first;

      first = table[i];
      if (first != NULL)
	{
	  struct table_elt *last = first;

	  table[i] = NULL;

	  while (last->next_same_hash != NULL)
	    last = last->next_same_hash;

	  /* Now relink this hash entire chain into
	     the free element list.  */

	  last->next_same_hash = free_element_chain;
	  free_element_chain = first;
	}
    }

  table_size = 0;

#ifdef HAVE_cc0
  prev_insn = 0;
  prev_insn_cc0 = 0;
#endif
}