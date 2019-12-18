#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {int /*<<< orphan*/  stmt; struct TYPE_3__* outer; } ;
typedef  TYPE_1__ omp_context ;

/* Variables and functions */
 int /*<<< orphan*/  OMP_CLAUSES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMP_CLAUSE_ORDERED ; 
#define  OMP_CRITICAL 134 
 int /*<<< orphan*/  OMP_CRITICAL_NAME (int /*<<< orphan*/ ) ; 
#define  OMP_FOR 133 
#define  OMP_MASTER 132 
#define  OMP_ORDERED 131 
#define  OMP_PARALLEL 130 
#define  OMP_SECTIONS 129 
#define  OMP_SINGLE 128 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_omp_clause (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
check_omp_nesting_restrictions (tree t, omp_context *ctx)
{
  switch (TREE_CODE (t))
    {
    case OMP_FOR:
    case OMP_SECTIONS:
    case OMP_SINGLE:
      for (; ctx != NULL; ctx = ctx->outer)
	switch (TREE_CODE (ctx->stmt))
	  {
	  case OMP_FOR:
	  case OMP_SECTIONS:
	  case OMP_SINGLE:
	  case OMP_ORDERED:
	  case OMP_MASTER:
	    warning (0, "work-sharing region may not be closely nested inside "
			"of work-sharing, critical, ordered or master region");
	    return;
	  case OMP_PARALLEL:
	    return;
	  default:
	    break;
	  }
      break;
    case OMP_MASTER:
      for (; ctx != NULL; ctx = ctx->outer)
	switch (TREE_CODE (ctx->stmt))
	  {
	  case OMP_FOR:
	  case OMP_SECTIONS:
	  case OMP_SINGLE:
	    warning (0, "master region may not be closely nested inside "
			"of work-sharing region");
	    return;
	  case OMP_PARALLEL:
	    return;
	  default:
	    break;
	  }
      break;
    case OMP_ORDERED:
      for (; ctx != NULL; ctx = ctx->outer)
	switch (TREE_CODE (ctx->stmt))
	  {
	  case OMP_CRITICAL:
	    warning (0, "ordered region may not be closely nested inside "
			"of critical region");
	    return;
	  case OMP_FOR:
	    if (find_omp_clause (OMP_CLAUSES (ctx->stmt),
				 OMP_CLAUSE_ORDERED) == NULL)
	      warning (0, "ordered region must be closely nested inside "
			  "a loop region with an ordered clause");
	    return;
	  case OMP_PARALLEL:
	    return;
	  default:
	    break;
	  }
      break;
    case OMP_CRITICAL:
      for (; ctx != NULL; ctx = ctx->outer)
	if (TREE_CODE (ctx->stmt) == OMP_CRITICAL
	    && OMP_CRITICAL_NAME (t) == OMP_CRITICAL_NAME (ctx->stmt))
	  {
	    warning (0, "critical region may not be nested inside a critical "
			"region with the same name");
	    return;
	  }
      break;
    default:
      break;
    }
}