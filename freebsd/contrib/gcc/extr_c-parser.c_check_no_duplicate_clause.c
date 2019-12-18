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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 scalar_t__ OMP_CLAUSE_CHAIN (scalar_t__) ; 
 int OMP_CLAUSE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 

__attribute__((used)) static void
check_no_duplicate_clause (tree clauses, enum tree_code code, const char *name)
{
  tree c;

  for (c = clauses; c ; c = OMP_CLAUSE_CHAIN (c))
    if (OMP_CLAUSE_CODE (c) == code)
      {
	error ("too many %qs clauses", name);
	break;
      }
}