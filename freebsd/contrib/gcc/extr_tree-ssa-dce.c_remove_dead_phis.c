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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_2__ {int /*<<< orphan*/  removed_phis; int /*<<< orphan*/  total_phis; } ;

/* Variables and functions */
 int /*<<< orphan*/  NECESSARY (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ PHI_CHAIN (scalar_t__) ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 scalar_t__ phi_nodes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_generic_stmt (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_phi_node (scalar_t__,scalar_t__) ; 
 TYPE_1__ stats ; 

__attribute__((used)) static void
remove_dead_phis (basic_block bb)
{
  tree prev, phi;

  prev = NULL_TREE;
  phi = phi_nodes (bb);
  while (phi)
    {
      stats.total_phis++;

      if (! NECESSARY (phi))
	{
	  tree next = PHI_CHAIN (phi);

	  if (dump_file && (dump_flags & TDF_DETAILS))
	    {
	      fprintf (dump_file, "Deleting : ");
	      print_generic_stmt (dump_file, phi, TDF_SLIM);
	      fprintf (dump_file, "\n");
	    }

	  remove_phi_node (phi, prev);
	  stats.removed_phis++;
	  phi = next;
	}
      else
	{
	  prev = phi;
	  phi = PHI_CHAIN (phi);
	}
    }
}