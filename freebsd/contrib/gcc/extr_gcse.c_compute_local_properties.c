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
struct occr {scalar_t__ copied_p; int /*<<< orphan*/  insn; struct occr* next; scalar_t__ deleted_p; } ;
struct hash_table {unsigned int size; scalar_t__ set_p; struct expr** table; } ;
struct expr {int bitmap_index; scalar_t__ reaching_reg; struct occr* avail_occr; struct occr* antic_occr; int /*<<< orphan*/  expr; struct expr* next_same_hash; } ;
typedef  int /*<<< orphan*/  sbitmap ;

/* Variables and functions */
 size_t BLOCK_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  compute_transp (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  last_basic_block ; 
 int /*<<< orphan*/  sbitmap_vector_ones (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_vector_zero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
compute_local_properties (sbitmap *transp, sbitmap *comp, sbitmap *antloc,
			  struct hash_table *table)
{
  unsigned int i;

  /* Initialize any bitmaps that were passed in.  */
  if (transp)
    {
      if (table->set_p)
	sbitmap_vector_zero (transp, last_basic_block);
      else
	sbitmap_vector_ones (transp, last_basic_block);
    }

  if (comp)
    sbitmap_vector_zero (comp, last_basic_block);
  if (antloc)
    sbitmap_vector_zero (antloc, last_basic_block);

  for (i = 0; i < table->size; i++)
    {
      struct expr *expr;

      for (expr = table->table[i]; expr != NULL; expr = expr->next_same_hash)
	{
	  int indx = expr->bitmap_index;
	  struct occr *occr;

	  /* The expression is transparent in this block if it is not killed.
	     We start by assuming all are transparent [none are killed], and
	     then reset the bits for those that are.  */
	  if (transp)
	    compute_transp (expr->expr, indx, transp, table->set_p);

	  /* The occurrences recorded in antic_occr are exactly those that
	     we want to set to nonzero in ANTLOC.  */
	  if (antloc)
	    for (occr = expr->antic_occr; occr != NULL; occr = occr->next)
	      {
		SET_BIT (antloc[BLOCK_NUM (occr->insn)], indx);

		/* While we're scanning the table, this is a good place to
		   initialize this.  */
		occr->deleted_p = 0;
	      }

	  /* The occurrences recorded in avail_occr are exactly those that
	     we want to set to nonzero in COMP.  */
	  if (comp)
	    for (occr = expr->avail_occr; occr != NULL; occr = occr->next)
	      {
		SET_BIT (comp[BLOCK_NUM (occr->insn)], indx);

		/* While we're scanning the table, this is a good place to
		   initialize this.  */
		occr->copied_p = 0;
	      }

	  /* While we're scanning the table, this is a good place to
	     initialize this.  */
	  expr->reaching_reg = 0;
	}
    }
}