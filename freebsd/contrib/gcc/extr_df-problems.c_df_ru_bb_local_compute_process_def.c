#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct df_ru_problem_data {int /*<<< orphan*/  use_sites; } ;
struct df_ru_bb_info {int /*<<< orphan*/  kill; int /*<<< orphan*/  sparse_kill; } ;
struct df_ref {struct df_ref* next_ref; } ;
struct df {int dummy; } ;
struct dataflow {scalar_t__ problem_data; struct df* df; } ;
typedef  enum df_ref_flags { ____Placeholder_df_ref_flags } df_ref_flags ;
typedef  int /*<<< orphan*/  bitmap ;
struct TYPE_2__ {unsigned int begin; unsigned int n_refs; } ;

/* Variables and functions */
 int DF_REF_AT_TOP ; 
 int DF_REF_FLAGS (struct df_ref*) ; 
 int DF_REF_PARTIAL ; 
 unsigned int DF_REF_REGNO (struct df_ref*) ; 
 TYPE_1__* DF_REG_USE_GET (struct df*,unsigned int) ; 
 unsigned int DF_SPARSE_THRESHOLD ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bitmap_ior_into (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  df_ref_bitmap (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  seen_in_block ; 
 int /*<<< orphan*/  seen_in_insn ; 

__attribute__((used)) static void
df_ru_bb_local_compute_process_def (struct dataflow *dflow,
				    struct df_ru_bb_info *bb_info, 
				    struct df_ref *def,
				    enum df_ref_flags top_flag)
{
  struct df *df = dflow->df;
  while (def)
    {
      if ((top_flag == (DF_REF_FLAGS (def) & DF_REF_AT_TOP))
	  /* If the def is to only part of the reg, it is as if it did
	     not happen, since some of the bits may get thru.  */
	  && (!(DF_REF_FLAGS (def) & DF_REF_PARTIAL)))
	{
	  unsigned int regno = DF_REF_REGNO (def);
	  unsigned int begin = DF_REG_USE_GET (df, regno)->begin;
	  unsigned int n_uses = DF_REG_USE_GET (df, regno)->n_refs;
	  if (!bitmap_bit_p (seen_in_block, regno))
	    {
	      /* The first def for regno in the insn, causes the kill
		 info to be generated.  Do not modify the gen set
		 because the only values in it are the uses from here
		 to the top of the block and this def does not effect
		 them.  */
	      if (!bitmap_bit_p (seen_in_insn, regno))
		{
		  if (n_uses > DF_SPARSE_THRESHOLD)
		    bitmap_set_bit (bb_info->sparse_kill, regno);
		  else
		    {
		      struct df_ru_problem_data * problem_data
			= (struct df_ru_problem_data *)dflow->problem_data;
		      bitmap uses 
			= df_ref_bitmap (problem_data->use_sites, regno, 
				       begin, n_uses);
		      bitmap_ior_into (bb_info->kill, uses);
		    }
		}
	      bitmap_set_bit (seen_in_insn, regno);
	    }
	}
      def = def->next_ref;
    }
}