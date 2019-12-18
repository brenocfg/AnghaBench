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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 int /*<<< orphan*/  build_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * eh_type_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_used (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptr_type_node ; 

__attribute__((used)) static tree
build_eh_type_type (tree type)
{
  tree exp = eh_type_info (type);

  if (!exp)
    return NULL;

  mark_used (exp);

  return convert (ptr_type_node, build_address (exp));
}