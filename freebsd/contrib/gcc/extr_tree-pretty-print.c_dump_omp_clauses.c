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
typedef  int /*<<< orphan*/ * tree ;
typedef  int /*<<< orphan*/  pretty_printer ;

/* Variables and functions */
 int /*<<< orphan*/ * OMP_CLAUSE_CHAIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_omp_clause (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pp_space (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dump_omp_clauses (pretty_printer *buffer, tree clause, int spc, int flags)
{
  if (clause == NULL)
    return;

  pp_space (buffer);
  while (1)
    {
      dump_omp_clause (buffer, clause, spc, flags);
      clause = OMP_CLAUSE_CHAIN (clause);
      if (clause == NULL)
	return;
      pp_space (buffer);
    }
}