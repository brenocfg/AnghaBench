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
struct TYPE_3__ {scalar_t__ groups_count; int /*<<< orphan*/ * groups; scalar_t__ elements_count; int /*<<< orphan*/ * elements; int /*<<< orphan*/ * param; scalar_t__ level; } ;
typedef  TYPE_1__ scope_t ;

/* Variables and functions */

void scope_init(scope_t *scope)
{
   scope->level          = 0;

   scope->param          = NULL;
   scope->elements       = NULL;
   scope->elements_count = 0;
   scope->groups         = NULL;
   scope->groups_count   = 0;
}