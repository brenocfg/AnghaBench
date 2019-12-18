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
typedef  int /*<<< orphan*/  cp_token ;
typedef  int /*<<< orphan*/  cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  c_finish_omp_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp_parser_omp_structured_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_require_pragma_eol (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
cp_parser_omp_master (cp_parser *parser, cp_token *pragma_tok)
{
  cp_parser_require_pragma_eol (parser, pragma_tok);
  return c_finish_omp_master (cp_parser_omp_structured_block (parser));
}