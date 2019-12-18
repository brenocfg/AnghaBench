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
typedef  int /*<<< orphan*/  HARD_REG_SET ;

/* Variables and functions */
 int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  GO_IF_HARD_REG_SUBSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  all_btrs ; 
 int /*<<< orphan*/  give_up ; 
 int* reg_alloc_order ; 

__attribute__((used)) static int
choose_btr (HARD_REG_SET used_btrs)
{
  int i;
  GO_IF_HARD_REG_SUBSET (all_btrs, used_btrs, give_up);

  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    {
#ifdef REG_ALLOC_ORDER
      int regno = reg_alloc_order[i];
#else
      int regno = i;
#endif
      if (TEST_HARD_REG_BIT (all_btrs, regno)
	  && !TEST_HARD_REG_BIT (used_btrs, regno))
	return regno;
    }
give_up:
  return -1;
}