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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_SAME_STMT ; 
 int /*<<< orphan*/  EXPR_LOCATION (scalar_t__) ; 
 int /*<<< orphan*/  EXPR_LOCUS (scalar_t__) ; 
 int /*<<< orphan*/  REPORT_DETAILS ; 
 int /*<<< orphan*/  SET_EXPR_LOCATION (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_EXPR_LOCUS (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 int /*<<< orphan*/  bsi_insert_before (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vect_dump ; 
 scalar_t__ vect_print_dump_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vect_finish_stmt_generation (tree stmt, tree vec_stmt, block_stmt_iterator *bsi)
{
  bsi_insert_before (bsi, vec_stmt, BSI_SAME_STMT);

  if (vect_print_dump_info (REPORT_DETAILS))
    {
      fprintf (vect_dump, "add new stmt: ");
      print_generic_expr (vect_dump, vec_stmt, TDF_SLIM);
    }

  /* Make sure bsi points to the stmt that is being vectorized.  */
  gcc_assert (stmt == bsi_stmt (*bsi));

#ifdef USE_MAPPED_LOCATION
  SET_EXPR_LOCATION (vec_stmt, EXPR_LOCATION (stmt));
#else
  SET_EXPR_LOCUS (vec_stmt, EXPR_LOCUS (stmt));
#endif
}