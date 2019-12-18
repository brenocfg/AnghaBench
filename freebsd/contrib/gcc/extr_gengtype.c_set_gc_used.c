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
typedef  TYPE_1__* pair_p ;
struct TYPE_3__ {int /*<<< orphan*/  type; struct TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC_USED ; 
 int /*<<< orphan*/  set_gc_used_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_gc_used (pair_p variables)
{
  pair_p p;
  for (p = variables; p; p = p->next)
    set_gc_used_type (p->type, GC_USED, NULL);
}