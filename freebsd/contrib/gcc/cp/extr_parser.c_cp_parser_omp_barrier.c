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
typedef  int /*<<< orphan*/  cp_token ;
typedef  int /*<<< orphan*/  cp_parser ;

/* Variables and functions */
 int /*<<< orphan*/  cp_parser_require_pragma_eol (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_omp_barrier () ; 

__attribute__((used)) static void
cp_parser_omp_barrier (cp_parser *parser, cp_token *pragma_tok)
{
  cp_parser_require_pragma_eol (parser, pragma_tok);
  finish_omp_barrier ();
}