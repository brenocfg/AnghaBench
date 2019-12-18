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
typedef  int /*<<< orphan*/  view_t ;
struct TYPE_3__ {int groups_count; int /*<<< orphan*/ * groups; } ;
typedef  TYPE_1__ scope_t ;

/* Variables and functions */
 int /*<<< orphan*/  vec_size (void**,int,int) ; 
 int /*<<< orphan*/  view_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

view_t *scope_add_group(scope_t *scope)
{
   view_t *group;

   vec_size((void**)&scope->groups, sizeof(view_t), ++scope->groups_count);

   group = &scope->groups[scope->groups_count - 1];
   view_init(group, NULL);

   return group;
}