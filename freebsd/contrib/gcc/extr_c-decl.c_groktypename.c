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
struct c_type_name {TYPE_1__* specs; int /*<<< orphan*/  declarator; } ;
struct TYPE_2__ {int /*<<< orphan*/  attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TYPENAME ; 
 int /*<<< orphan*/  decl_attributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grokdeclarator (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

tree
groktypename (struct c_type_name *type_name)
{
  tree type;
  tree attrs = type_name->specs->attrs;

  type_name->specs->attrs = NULL_TREE;

  type = grokdeclarator (type_name->declarator, type_name->specs, TYPENAME,
			 false, NULL);

  /* Apply attributes.  */
  decl_attributes (&type, attrs, 0);

  return type;
}