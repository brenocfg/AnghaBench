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
struct df_ru_bb_info {int /*<<< orphan*/  gen; } ;
struct df_ref {struct df_ref* next_ref; } ;
typedef  enum df_ref_flags { ____Placeholder_df_ref_flags } df_ref_flags ;

/* Variables and functions */
 int DF_REF_AT_TOP ; 
 int DF_REF_FLAGS (struct df_ref*) ; 
 int /*<<< orphan*/  DF_REF_ID (struct df_ref*) ; 
 unsigned int DF_REF_REGNO (struct df_ref*) ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seen_in_block ; 

__attribute__((used)) static void
df_ru_bb_local_compute_process_use (struct df_ru_bb_info *bb_info, 
				    struct df_ref *use,
				    enum df_ref_flags top_flag)
{
  while (use)
    {
      if (top_flag == (DF_REF_FLAGS (use) & DF_REF_AT_TOP))
	{
	  /* Add use to set of gens in this BB unless we have seen a
	     def in a previous instruction.  */
	  unsigned int regno = DF_REF_REGNO (use);
	  if (!bitmap_bit_p (seen_in_block, regno))
	    bitmap_set_bit (bb_info->gen, DF_REF_ID (use));
	}
      use = use->next_ref;
    }
}