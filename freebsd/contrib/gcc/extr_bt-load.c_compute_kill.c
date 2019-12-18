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
typedef  int /*<<< orphan*/  sbitmap ;
typedef  int /*<<< orphan*/  HARD_REG_SET ;

/* Variables and functions */
 int NUM_FIXED_BLOCKS ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  all_btrs ; 
 int first_btr ; 
 int last_btr ; 
 int n_basic_blocks ; 
 int /*<<< orphan*/  sbitmap_a_or_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_vector_zero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
compute_kill (sbitmap *bb_kill, sbitmap *btr_defset,
	      HARD_REG_SET *btrs_written)
{
  int i;
  int regno;

  /* For each basic block, form the set BB_KILL - the set
     of definitions that the block kills.  */
  sbitmap_vector_zero (bb_kill, n_basic_blocks);
  for (i = NUM_FIXED_BLOCKS; i < n_basic_blocks; i++)
    {
      for (regno = first_btr; regno <= last_btr; regno++)
	if (TEST_HARD_REG_BIT (all_btrs, regno)
	    && TEST_HARD_REG_BIT (btrs_written[i], regno))
	  sbitmap_a_or_b (bb_kill[i], bb_kill[i],
			  btr_defset[regno - first_btr]);
    }
}