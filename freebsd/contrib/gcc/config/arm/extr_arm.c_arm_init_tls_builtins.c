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
typedef  int /*<<< orphan*/ * tree ;
struct TYPE_2__ {int /*<<< orphan*/  (* builtin_function ) (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_BUILTIN_THREAD_POINTER ; 
 int /*<<< orphan*/  BUILT_IN_MD ; 
 int /*<<< orphan*/ * build_function_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 TYPE_1__ lang_hooks ; 
 int /*<<< orphan*/  ptr_type_node ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  void_list_node ; 

__attribute__((used)) static void
arm_init_tls_builtins (void)
{
  tree ftype;
  tree nothrow = tree_cons (get_identifier ("nothrow"), NULL, NULL);
  tree const_nothrow = tree_cons (get_identifier ("const"), NULL, nothrow);

  ftype = build_function_type (ptr_type_node, void_list_node);
  lang_hooks.builtin_function ("__builtin_thread_pointer", ftype,
			       ARM_BUILTIN_THREAD_POINTER, BUILT_IN_MD,
			       NULL, const_nothrow);
}