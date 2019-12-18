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
 int /*<<< orphan*/  DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_DECLARED_INLINE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_FUNCTION_MEMBER_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_MAIN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NAMESPACE_SCOPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NON_THUNK_FUNCTION_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_Wmissing_prototypes ; 
 scalar_t__ TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decl_anon_ns_mem_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fn_previously_found (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  namespace_binding (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ namespace_bindings_p () ; 
 scalar_t__ warn_missing_prototypes ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static void
check_missing_prototype (tree decl)
{
  if (warn_missing_prototypes
      && namespace_bindings_p ()
      && TREE_PUBLIC (decl)
      && !DECL_MAIN_P (decl)
      && DECL_NON_THUNK_FUNCTION_P (decl)
      && ! DECL_FUNCTION_MEMBER_P (decl)
      && DECL_NAMESPACE_SCOPE_P (decl)
      && ! decl_anon_ns_mem_p (decl)
      && ! DECL_DECLARED_INLINE_P (decl))
    {
      tree olddecl = namespace_binding (DECL_NAME (decl),  DECL_CONTEXT (decl));
      if (!fn_previously_found (decl, olddecl))
	warning (OPT_Wmissing_prototypes, "no previous prototype for %q+D", decl);
    }
}