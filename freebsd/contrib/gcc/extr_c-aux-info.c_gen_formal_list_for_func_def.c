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
typedef  int /*<<< orphan*/  formals_style ;

/* Variables and functions */
 scalar_t__ DECL_ARGUMENTS (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  ansi ; 
 char* concat (char const*,char const*,char*,...) ; 
 scalar_t__ deserves_ellipsis (int /*<<< orphan*/ ) ; 
 char* gen_decl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_and_r_decls ; 
 int /*<<< orphan*/  k_and_r_names ; 

__attribute__((used)) static const char *
gen_formal_list_for_func_def (tree fndecl, formals_style style)
{
  const char *formal_list = "";
  tree formal_decl;

  formal_decl = DECL_ARGUMENTS (fndecl);
  while (formal_decl)
    {
      const char *this_formal;

      if (*formal_list && ((style == ansi) || (style == k_and_r_names)))
	formal_list = concat (formal_list, ", ", NULL);
      this_formal = gen_decl (formal_decl, 0, style);
      if (style == k_and_r_decls)
	formal_list = concat (formal_list, this_formal, "; ", NULL);
      else
	formal_list = concat (formal_list, this_formal, NULL);
      formal_decl = TREE_CHAIN (formal_decl);
    }
  if (style == ansi)
    {
      if (!DECL_ARGUMENTS (fndecl))
	formal_list = concat (formal_list, "void", NULL);
      if (deserves_ellipsis (TREE_TYPE (fndecl)))
	formal_list = concat (formal_list, ", ...", NULL);
    }
  if ((style == ansi) || (style == k_and_r_names))
    formal_list = concat (" (", formal_list, ")", NULL);
  return formal_list;
}