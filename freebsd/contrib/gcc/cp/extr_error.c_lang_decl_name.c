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
 int /*<<< orphan*/  CP_DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_CLASS_SCOPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 int /*<<< orphan*/  TFF_DECL_SPECIFIERS ; 
 int /*<<< orphan*/  TFF_PLAIN_IDENTIFIER ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxx_pp ; 
 char const* decl_as_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_function_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_colon_colon (int /*<<< orphan*/ ) ; 
 char const* pp_formatted_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_cxx_pp () ; 

const char *
lang_decl_name (tree decl, int v)
{
  if (v >= 2)
    return decl_as_string (decl, TFF_DECL_SPECIFIERS);

  reinit_cxx_pp ();
  if (v == 1 && DECL_CLASS_SCOPE_P (decl))
    {
      dump_type (CP_DECL_CONTEXT (decl), TFF_PLAIN_IDENTIFIER);
      pp_cxx_colon_colon (cxx_pp);
    }

  if (TREE_CODE (decl) == FUNCTION_DECL)
    dump_function_name (decl, TFF_PLAIN_IDENTIFIER);
  else
    dump_decl (DECL_NAME (decl), TFF_PLAIN_IDENTIFIER);

  return pp_formatted_text (cxx_pp);
}