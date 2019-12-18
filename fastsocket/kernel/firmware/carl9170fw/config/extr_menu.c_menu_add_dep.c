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
struct expr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dep; } ;

/* Variables and functions */
 TYPE_1__* current_entry ; 
 int /*<<< orphan*/  expr_alloc_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_check_dep (struct expr*) ; 

void menu_add_dep(struct expr *dep)
{
	current_entry->dep = expr_alloc_and(current_entry->dep, menu_check_dep(dep));
}