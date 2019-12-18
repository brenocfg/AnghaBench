#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {int /*<<< orphan*/  src_fn; } ;
typedef  TYPE_1__ copy_body_data ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_SAVED_TREE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_body_r ; 
 int /*<<< orphan*/  walk_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
copy_generic_body (copy_body_data *id)
{
  tree body;
  tree fndecl = id->src_fn;

  body = DECL_SAVED_TREE (fndecl);
  walk_tree (&body, copy_body_r, id, NULL);

  return body;
}