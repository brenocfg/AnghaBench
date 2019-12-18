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
 int /*<<< orphan*/  CLASSTYPE_TI_TEMPLATE (int /*<<< orphan*/ ) ; 
 scalar_t__ CLASSTYPE_USE_TEMPLATE (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_ARTIFICIAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ PRIMARY_TEMPLATE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ constructor_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
template_self_reference_p (tree type, tree decl)
{
  return  (CLASSTYPE_USE_TEMPLATE (type)
	   && PRIMARY_TEMPLATE_P (CLASSTYPE_TI_TEMPLATE (type))
	   && TREE_CODE (decl) == TYPE_DECL
	   && DECL_ARTIFICIAL (decl)
	   && DECL_NAME (decl) == constructor_name (type));
}