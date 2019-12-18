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
struct omp_region {scalar_t__ exit; scalar_t__ entry; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  scalar_t__ basic_block ;
struct TYPE_2__ {void* flags; } ;

/* Variables and functions */
 void* EDGE_FALLTHRU ; 
 scalar_t__ OMP_CRITICAL ; 
 scalar_t__ OMP_MASTER ; 
 scalar_t__ OMP_ORDERED ; 
 scalar_t__ OMP_RETURN ; 
 scalar_t__ OMP_SINGLE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (scalar_t__) ; 
 int /*<<< orphan*/  bsi_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* single_succ_edge (scalar_t__) ; 

__attribute__((used)) static void
expand_omp_synch (struct omp_region *region)
{
  basic_block entry_bb, exit_bb;
  block_stmt_iterator si;

  entry_bb = region->entry;
  exit_bb = region->exit;

  si = bsi_last (entry_bb);
  gcc_assert (TREE_CODE (bsi_stmt (si)) == OMP_SINGLE
	      || TREE_CODE (bsi_stmt (si)) == OMP_MASTER
	      || TREE_CODE (bsi_stmt (si)) == OMP_ORDERED
	      || TREE_CODE (bsi_stmt (si)) == OMP_CRITICAL);
  bsi_remove (&si, true);
  single_succ_edge (entry_bb)->flags = EDGE_FALLTHRU;

  if (exit_bb)
    {
      si = bsi_last (exit_bb);
      gcc_assert (TREE_CODE (bsi_stmt (si)) == OMP_RETURN);
      bsi_remove (&si, true);
      single_succ_edge (exit_bb)->flags = EDGE_FALLTHRU;
    }
}