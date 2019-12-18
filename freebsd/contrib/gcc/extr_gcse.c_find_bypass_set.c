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
struct expr {int /*<<< orphan*/  expr; int /*<<< orphan*/  bitmap_index; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cprop_avout ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ gcse_constant_p (int /*<<< orphan*/ ) ; 
 struct expr* lookup_set (int,int /*<<< orphan*/ *) ; 
 struct expr* next_set (int,struct expr*) ; 
 int /*<<< orphan*/  set_hash_table ; 

__attribute__((used)) static struct expr *
find_bypass_set (int regno, int bb)
{
  struct expr *result = 0;

  for (;;)
    {
      rtx src;
      struct expr *set = lookup_set (regno, &set_hash_table);

      while (set)
	{
	  if (TEST_BIT (cprop_avout[bb], set->bitmap_index))
	    break;
	  set = next_set (regno, set);
	}

      if (set == 0)
	break;

      gcc_assert (GET_CODE (set->expr) == SET);

      src = SET_SRC (set->expr);
      if (gcse_constant_p (src))
	result = set;

      if (! REG_P (src))
	break;

      regno = REGNO (src);
    }
  return result;
}