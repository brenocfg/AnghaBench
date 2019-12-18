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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
 scalar_t__ DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_cxx_left_brace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_nested_name_specifier (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pp_cxx_right_brace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_unqualified_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_whitespace (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_cxx_original_namespace_definition (cxx_pretty_printer *pp, tree t)
{
  pp_cxx_identifier (pp, "namespace");
  if (DECL_CONTEXT (t))
    pp_cxx_nested_name_specifier (pp, DECL_CONTEXT (t));
  if (DECL_NAME (t))
    pp_cxx_unqualified_id (pp, t);
  pp_cxx_whitespace (pp);
  pp_cxx_left_brace (pp);
  /* We do not print the namespace-body.  */
  pp_cxx_whitespace (pp);
  pp_cxx_right_brace (pp);
}