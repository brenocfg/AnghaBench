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
typedef  int /*<<< orphan*/  tree ;
struct omp_region {int /*<<< orphan*/  exit; int /*<<< orphan*/  entry; } ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;
struct TYPE_2__ {void* flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_SAME_STMT ; 
 void* EDGE_FALLTHRU ; 
 int /*<<< orphan*/  OMP_CLAUSE_COPYPRIVATE ; 
 int /*<<< orphan*/  OMP_RETURN_NOWAIT (int /*<<< orphan*/ ) ; 
 scalar_t__ OMP_SINGLE ; 
 int /*<<< orphan*/  OMP_SINGLE_CLAUSES (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_stmt_list () ; 
 int /*<<< orphan*/  bsi_insert_after (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_omp_barrier (int /*<<< orphan*/ *) ; 
 scalar_t__ find_omp_clause (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* single_succ_edge (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
expand_omp_single (struct omp_region *region)
{
  basic_block entry_bb, exit_bb;
  block_stmt_iterator si;
  bool need_barrier = false;

  entry_bb = region->entry;
  exit_bb = region->exit;

  si = bsi_last (entry_bb);
  /* The terminal barrier at the end of a GOMP_single_copy sequence cannot
     be removed.  We need to ensure that the thread that entered the single
     does not exit before the data is copied out by the other threads.  */
  if (find_omp_clause (OMP_SINGLE_CLAUSES (bsi_stmt (si)),
		       OMP_CLAUSE_COPYPRIVATE))
    need_barrier = true;
  gcc_assert (TREE_CODE (bsi_stmt (si)) == OMP_SINGLE);
  bsi_remove (&si, true);
  single_succ_edge (entry_bb)->flags = EDGE_FALLTHRU;

  si = bsi_last (exit_bb);
  if (!OMP_RETURN_NOWAIT (bsi_stmt (si)) || need_barrier)
    {
      tree t = alloc_stmt_list ();
      build_omp_barrier (&t);
      bsi_insert_after (&si, t, BSI_SAME_STMT);
    }
  bsi_remove (&si, true);
  single_succ_edge (exit_bb)->flags = EDGE_FALLTHRU;
}