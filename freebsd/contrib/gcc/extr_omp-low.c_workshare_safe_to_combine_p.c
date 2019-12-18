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
typedef  int /*<<< orphan*/  tree ;
struct omp_for_data {scalar_t__ chunk_size; scalar_t__ step; scalar_t__ n2; scalar_t__ n1; } ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ OMP_FOR ; 
 scalar_t__ OMP_SECTIONS ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_omp_for_data (int /*<<< orphan*/ ,struct omp_for_data*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  is_gimple_min_invariant (scalar_t__) ; 
 int /*<<< orphan*/  last_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
workshare_safe_to_combine_p (basic_block par_entry_bb, basic_block ws_entry_bb)
{
  struct omp_for_data fd;
  tree par_stmt, ws_stmt;

  par_stmt = last_stmt (par_entry_bb);
  ws_stmt = last_stmt (ws_entry_bb);

  if (TREE_CODE (ws_stmt) == OMP_SECTIONS)
    return true;

  gcc_assert (TREE_CODE (ws_stmt) == OMP_FOR);

  extract_omp_for_data (ws_stmt, &fd);

  /* FIXME.  We give up too easily here.  If any of these arguments
     are not constants, they will likely involve variables that have
     been mapped into fields of .omp_data_s for sharing with the child
     function.  With appropriate data flow, it would be possible to
     see through this.  */
  if (!is_gimple_min_invariant (fd.n1)
      || !is_gimple_min_invariant (fd.n2)
      || !is_gimple_min_invariant (fd.step)
      || (fd.chunk_size && !is_gimple_min_invariant (fd.chunk_size)))
    return false;

  return true;
}