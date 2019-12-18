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
typedef  int /*<<< orphan*/  mfsplay_tree_key ;
typedef  int /*<<< orphan*/  mfsplay_tree ;
struct TYPE_3__ {scalar_t__ low; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ __mf_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  __mf_object_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfsplay_tree_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__mf_unlink_object (__mf_object_t *node)
{
  mfsplay_tree t = __mf_object_tree (node->type);
  mfsplay_tree_remove (t, (mfsplay_tree_key) node->low);
}