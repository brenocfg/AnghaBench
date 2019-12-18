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
typedef  int /*<<< orphan*/  cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  begin_omp_structured_block () ; 
 unsigned int cp_parser_begin_omp_structured_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_end_omp_structured_block (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  cp_parser_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_omp_structured_block (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
cp_parser_omp_structured_block (cp_parser *parser)
{
  tree stmt = begin_omp_structured_block ();
  unsigned int save = cp_parser_begin_omp_structured_block (parser);

  cp_parser_statement (parser, NULL_TREE, false, NULL);

  cp_parser_end_omp_structured_block (parser, save);
  return finish_omp_structured_block (stmt);
}