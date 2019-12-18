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
 int /*<<< orphan*/  DECL_INITIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ TEMPLATE_PARM_INDEX ; 
 int TFF_DECL_SPECIFIERS ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_decl (scalar_t__,int) ; 
 int /*<<< orphan*/  dump_scope (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_type_prefix (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_type_suffix (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pp_identifier (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pp_maybe_space (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_simple_decl (tree t, tree type, int flags)
{
  if (flags & TFF_DECL_SPECIFIERS)
    {
      dump_type_prefix (type, flags);
      pp_maybe_space (cxx_pp);
    }
  if (!DECL_INITIAL (t) || TREE_CODE (DECL_INITIAL (t)) != TEMPLATE_PARM_INDEX)
    dump_scope (CP_DECL_CONTEXT (t), flags);
  if (DECL_NAME (t))
    dump_decl (DECL_NAME (t), flags);
  else
    pp_identifier (cxx_pp, "<anonymous>");
  if (flags & TFF_DECL_SPECIFIERS)
    dump_type_suffix (type, flags);
}