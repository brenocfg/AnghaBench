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
typedef  int /*<<< orphan*/  c_parser ;

/* Variables and functions */
 int /*<<< orphan*/  OMP_CLAUSE_LASTPRIVATE ; 
 int /*<<< orphan*/  c_parser_omp_var_list_parens (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
c_parser_omp_clause_lastprivate (c_parser *parser, tree list)
{
  return c_parser_omp_var_list_parens (parser, OMP_CLAUSE_LASTPRIVATE, list);
}