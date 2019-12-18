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
union parameter_info {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/ * tree ;
typedef  enum cvalue_type { ____Placeholder_cvalue_type } cvalue_type ;

/* Variables and functions */
 int /*<<< orphan*/ * fold_convert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipcp_type_is_const (int) ; 

__attribute__((used)) static tree
build_const_val (union parameter_info *cvalue, enum cvalue_type type,
		 tree tree_type)
{
  tree const_val = NULL;

  gcc_assert (ipcp_type_is_const (type));
  const_val = fold_convert (tree_type, cvalue->value);
  return const_val;
}