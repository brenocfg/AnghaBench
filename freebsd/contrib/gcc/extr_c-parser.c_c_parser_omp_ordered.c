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
 int /*<<< orphan*/  c_finish_omp_ordered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_parser_omp_structured_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  c_parser_skip_to_pragma_eol (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
c_parser_omp_ordered (c_parser *parser)
{
  c_parser_skip_to_pragma_eol (parser);
  return c_finish_omp_ordered (c_parser_omp_structured_block (parser));
}