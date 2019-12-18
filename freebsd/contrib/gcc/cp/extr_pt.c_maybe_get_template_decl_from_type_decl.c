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
 scalar_t__ CLASSTYPE_TEMPLATE_INFO (int /*<<< orphan*/ ) ; 
 scalar_t__ CLASSTYPE_TI_TEMPLATE (int /*<<< orphan*/ ) ; 
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_ARTIFICIAL (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 

tree
maybe_get_template_decl_from_type_decl (tree decl)
{
  return (decl != NULL_TREE
	  && TREE_CODE (decl) == TYPE_DECL
	  && DECL_ARTIFICIAL (decl)
	  && CLASS_TYPE_P (TREE_TYPE (decl))
	  && CLASSTYPE_TEMPLATE_INFO (TREE_TYPE (decl)))
    ? CLASSTYPE_TI_TEMPLATE (TREE_TYPE (decl)) : decl;
}