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

/* Variables and functions */
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* pp_formatted_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_cxx_pp () ; 

__attribute__((used)) static const char *
expr_to_string (tree decl)
{
  reinit_cxx_pp ();
  dump_expr (decl, 0);
  return pp_formatted_text (cxx_pp);
}