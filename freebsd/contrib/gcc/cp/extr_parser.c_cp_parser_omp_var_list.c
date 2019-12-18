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
typedef  enum omp_clause_code { ____Placeholder_omp_clause_code } omp_clause_code ;
typedef  int /*<<< orphan*/  cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_OPEN_PAREN ; 
 int /*<<< orphan*/  cp_parser_omp_var_list_no_open (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ cp_parser_require (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static tree
cp_parser_omp_var_list (cp_parser *parser, enum omp_clause_code kind, tree list)
{
  if (cp_parser_require (parser, CPP_OPEN_PAREN, "`('"))
    return cp_parser_omp_var_list_no_open (parser, kind, list);
  return list;
}