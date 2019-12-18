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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 int TFF_CLASS_KEY_OR_ENUM ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  error_type (scalar_t__) ; 
 scalar_t__ null_node ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ ,char*) ; 
 char const* pp_formatted_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_separate_with_comma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_cxx_pp () ; 
 char const* type_as_string (scalar_t__,int) ; 

__attribute__((used)) static const char *
args_to_string (tree p, int verbose)
{
  int flags = 0;
  if (verbose)
    flags |= TFF_CLASS_KEY_OR_ENUM;

  if (p == NULL_TREE)
    return "";

  if (TYPE_P (TREE_VALUE (p)))
    return type_as_string (p, flags);

  reinit_cxx_pp ();
  for (; p; p = TREE_CHAIN (p))
    {
      if (TREE_VALUE (p) == null_node)
	pp_cxx_identifier (cxx_pp, "NULL");
      else
	dump_type (error_type (TREE_VALUE (p)), flags);
      if (TREE_CHAIN (p))
	pp_separate_with_comma (cxx_pp);
    }
  return pp_formatted_text (cxx_pp);
}