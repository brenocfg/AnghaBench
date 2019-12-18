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
struct table_elt {struct table_elt* prev_same_hash; struct table_elt* next_same_hash; int /*<<< orphan*/  mode; int /*<<< orphan*/  exp; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 unsigned int HASH_SIZE ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_IN_TABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_TICK (int /*<<< orphan*/ ) ; 
 unsigned int SAFE_HASH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ exp_equiv_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ reg_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct table_elt** table ; 

__attribute__((used)) static void
rehash_using_reg (rtx x)
{
  unsigned int i;
  struct table_elt *p, *next;
  unsigned hash;

  if (GET_CODE (x) == SUBREG)
    x = SUBREG_REG (x);

  /* If X is not a register or if the register is known not to be in any
     valid entries in the table, we have no work to do.  */

  if (!REG_P (x)
      || REG_IN_TABLE (REGNO (x)) < 0
      || REG_IN_TABLE (REGNO (x)) != REG_TICK (REGNO (x)))
    return;

  /* Scan all hash chains looking for valid entries that mention X.
     If we find one and it is in the wrong hash chain, move it.  */

  for (i = 0; i < HASH_SIZE; i++)
    for (p = table[i]; p; p = next)
      {
	next = p->next_same_hash;
	if (reg_mentioned_p (x, p->exp)
	    && exp_equiv_p (p->exp, p->exp, 1, false)
	    && i != (hash = SAFE_HASH (p->exp, p->mode)))
	  {
	    if (p->next_same_hash)
	      p->next_same_hash->prev_same_hash = p->prev_same_hash;

	    if (p->prev_same_hash)
	      p->prev_same_hash->next_same_hash = p->next_same_hash;
	    else
	      table[i] = p->next_same_hash;

	    p->next_same_hash = table[hash];
	    p->prev_same_hash = 0;
	    if (table[hash])
	      table[hash]->prev_same_hash = p;
	    table[hash] = p;
	  }
      }
}