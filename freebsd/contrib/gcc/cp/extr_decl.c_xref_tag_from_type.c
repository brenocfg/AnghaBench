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
typedef  int /*<<< orphan*/  tag_scope ;
typedef  enum tag_types { ____Placeholder_tag_types } tag_types ;

/* Variables and functions */
 scalar_t__ CLASSTYPE_DECLARED_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ RECORD_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_IDENTIFIER (int /*<<< orphan*/ ) ; 
 int class_type ; 
 int record_type ; 
 int union_type ; 
 int /*<<< orphan*/  xref_tag (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

tree
xref_tag_from_type (tree old, tree id, tag_scope scope)
{
  enum tag_types tag_kind;

  if (TREE_CODE (old) == RECORD_TYPE)
    tag_kind = (CLASSTYPE_DECLARED_CLASS (old) ? class_type : record_type);
  else
    tag_kind  = union_type;

  if (id == NULL_TREE)
    id = TYPE_IDENTIFIER (old);

  return xref_tag (tag_kind, id, scope, false);
}