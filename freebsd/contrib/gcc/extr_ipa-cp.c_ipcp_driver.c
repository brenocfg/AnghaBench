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
 int /*<<< orphan*/  cgraph_remove_unreachable_nodes (int,int /*<<< orphan*/ *) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  ipa_edges_create () ; 
 int /*<<< orphan*/  ipa_edges_free () ; 
 int /*<<< orphan*/  ipa_free () ; 
 int /*<<< orphan*/  ipa_nodes_create () ; 
 int /*<<< orphan*/  ipa_nodes_free () ; 
 int /*<<< orphan*/  ipcp_init_stage () ; 
 int /*<<< orphan*/  ipcp_insert_stage () ; 
 int /*<<< orphan*/  ipcp_iterate_stage () ; 
 int /*<<< orphan*/  ipcp_profile_print (scalar_t__) ; 
 int /*<<< orphan*/  ipcp_structures_print (scalar_t__) ; 

unsigned int
ipcp_driver (void)
{
  if (dump_file)
    fprintf (dump_file, "\nIPA constant propagation start:\n");
  ipa_nodes_create ();
  ipa_edges_create ();
  /* 1. Call the init stage to initialize 
     the ipa_node and ipa_edge structures.  */
  ipcp_init_stage ();
  if (dump_file)
    {
      fprintf (dump_file, "\nIPA structures before propagation:\n");
      ipcp_structures_print (dump_file);
    }
  /* 2. Do the interprocedural propagation.  */
  ipcp_iterate_stage ();
  if (dump_file)
    {
      fprintf (dump_file, "\nIPA structures after propagation:\n");
      ipcp_structures_print (dump_file);
      fprintf (dump_file, "\nProfiling info before insert stage:\n");
      ipcp_profile_print (dump_file);
    }
  /* 3. Insert the constants found to the functions.  */
  ipcp_insert_stage ();
  if (dump_file)
    {
      fprintf (dump_file, "\nProfiling info after insert stage:\n");
      ipcp_profile_print (dump_file);
    }
  /* Free all IPCP structures.  */
  ipa_free ();
  ipa_nodes_free ();
  ipa_edges_free ();
  if (dump_file)
    fprintf (dump_file, "\nIPA constant propagation end\n");
  cgraph_remove_unreachable_nodes (true, NULL);
  return 0;
}