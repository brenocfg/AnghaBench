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

/* Variables and functions */
 int /*<<< orphan*/  add_noreturn_fake_exit_edges () ; 
 void* ae_kill ; 
 void* antloc ; 
 void* comp ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  edge_list ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 size_t htab_elements (int /*<<< orphan*/ ) ; 
 int last_bb ; 
 int /*<<< orphan*/  pre_delete_map ; 
 int /*<<< orphan*/  pre_edge_lcm (size_t,void*,void*,void*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pre_insert_map ; 
 int /*<<< orphan*/  remove_fake_exit_edges () ; 
 void* sbitmap_vector_alloc (int,size_t) ; 
 int /*<<< orphan*/  sbitmap_vector_ones (void*,int) ; 
 int /*<<< orphan*/  sbitmap_vector_zero (void*,int) ; 
 int /*<<< orphan*/  see_analyze_ref_local_prop ; 
 scalar_t__* see_bb_splay_ar ; 
 int /*<<< orphan*/  see_pre_extension_hash ; 
 int /*<<< orphan*/  splay_tree_foreach (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* transp ; 

__attribute__((used)) static void
see_execute_LCM (void)
{
  size_t pre_extension_num = htab_elements (see_pre_extension_hash);
  int i = 0;

  if (dump_file)
    fprintf (dump_file,
      "* Phase 3: Eliminate globally redundant extensions.  *\n");

  /* Initialize the global sbitmap vectors.  */
  transp = sbitmap_vector_alloc (last_bb, pre_extension_num);
  comp = sbitmap_vector_alloc (last_bb, pre_extension_num);
  antloc = sbitmap_vector_alloc (last_bb, pre_extension_num);
  ae_kill = sbitmap_vector_alloc (last_bb, pre_extension_num);
  sbitmap_vector_ones (transp, last_bb);
  sbitmap_vector_zero (comp, last_bb);
  sbitmap_vector_zero (antloc, last_bb);
  sbitmap_vector_zero (ae_kill, last_bb);

  /* Traverse over all the splay trees of the basic blocks.  */
  for (i = 0; i < last_bb; i++)
    {
      if (see_bb_splay_ar[i])
	{
	  /* Traverse over all the references in the basic block in forward
	     order.  */
	  splay_tree_foreach (see_bb_splay_ar[i],
			      see_analyze_ref_local_prop, NULL);
	}
    }

  /* Add fake exit edges before running the lcm.  */
  add_noreturn_fake_exit_edges ();

  /* Run the LCM.  */
  edge_list = pre_edge_lcm (pre_extension_num, transp, comp, antloc,
  			    ae_kill, &pre_insert_map, &pre_delete_map);

  /* Remove the fake edges.  */
  remove_fake_exit_edges ();
}