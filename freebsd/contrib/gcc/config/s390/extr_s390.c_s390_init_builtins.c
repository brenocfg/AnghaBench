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
struct TYPE_2__ {int /*<<< orphan*/  (* builtin_function ) (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILT_IN_MD ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  S390_BUILTIN_SET_THREAD_POINTER ; 
 int /*<<< orphan*/  S390_BUILTIN_THREAD_POINTER ; 
 int /*<<< orphan*/  build_function_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_function_type_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ lang_hooks ; 
 int /*<<< orphan*/  ptr_type_node ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  void_list_node ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
s390_init_builtins (void)
{
  tree ftype;

  ftype = build_function_type (ptr_type_node, void_list_node);
  lang_hooks.builtin_function ("__builtin_thread_pointer", ftype,
			       S390_BUILTIN_THREAD_POINTER, BUILT_IN_MD,
			       NULL, NULL_TREE);

  ftype = build_function_type_list (void_type_node, ptr_type_node, NULL_TREE);
  lang_hooks.builtin_function ("__builtin_set_thread_pointer", ftype,
			       S390_BUILTIN_SET_THREAD_POINTER, BUILT_IN_MD,
			       NULL, NULL_TREE);
}