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
typedef  int /*<<< orphan*/  view_t ;
typedef  int /*<<< orphan*/  scope_t ;
typedef  int /*<<< orphan*/  rxml_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  load_view (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * scope_add_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scope_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scope_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool load_group(scope_t *scope, rxml_node_t *node)
{
   bool result = true;

   view_t *group = scope_add_group(scope);

   scope_push(scope);

   if (!load_view(scope, group, node, true))
      result = false;

   scope_pop(scope);

   return result;
}