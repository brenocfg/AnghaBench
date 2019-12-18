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
struct table_elt {scalar_t__ exp; int mode; struct table_elt* next_same_hash; } ;
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 unsigned int REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ exp_equiv_p (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct table_elt** table ; 

__attribute__((used)) static struct table_elt *
lookup_for_remove (rtx x, unsigned int hash, enum machine_mode mode)
{
  struct table_elt *p;

  if (REG_P (x))
    {
      unsigned int regno = REGNO (x);

      /* Don't check the machine mode when comparing registers;
	 invalidating (REG:SI 0) also invalidates (REG:DF 0).  */
      for (p = table[hash]; p; p = p->next_same_hash)
	if (REG_P (p->exp)
	    && REGNO (p->exp) == regno)
	  return p;
    }
  else
    {
      for (p = table[hash]; p; p = p->next_same_hash)
	if (mode == p->mode
	    && (x == p->exp || exp_equiv_p (x, p->exp, 0, false)))
	  return p;
    }

  return 0;
}