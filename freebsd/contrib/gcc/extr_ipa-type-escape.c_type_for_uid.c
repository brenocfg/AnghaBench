#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
typedef  TYPE_1__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 TYPE_1__* splay_tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_to_canon_type ; 

__attribute__((used)) static tree
type_for_uid (int uid)
{
  splay_tree_node result = 
    splay_tree_lookup (uid_to_canon_type, (splay_tree_key) uid);
  
  if (result)
    return (tree) result->value;  
  else return NULL;
}