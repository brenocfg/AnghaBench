#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  cp_token ;
typedef  int /*<<< orphan*/  cp_parser ;
struct TYPE_2__ {int /*<<< orphan*/  have_tls; } ;

/* Variables and functions */
 int /*<<< orphan*/  cp_parser_omp_var_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cp_parser_require_pragma_eol (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_omp_threadprivate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sorry (char*) ; 
 TYPE_1__ targetm ; 

__attribute__((used)) static void
cp_parser_omp_threadprivate (cp_parser *parser, cp_token *pragma_tok)
{
  tree vars;

  vars = cp_parser_omp_var_list (parser, 0, NULL);
  cp_parser_require_pragma_eol (parser, pragma_tok);

  if (!targetm.have_tls)
    sorry ("threadprivate variables not supported in this target");

  finish_omp_threadprivate (vars);
}