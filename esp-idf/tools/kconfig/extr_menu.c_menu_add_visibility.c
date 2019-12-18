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
struct TYPE_2__ {int /*<<< orphan*/  visibility; } ;

/* Variables and functions */
 TYPE_1__* current_entry ; 
 int /*<<< orphan*/  expr_alloc_and (int /*<<< orphan*/ ,struct expr*) ; 

void menu_add_visibility(struct expr *expr)
{
	current_entry->visibility = expr_alloc_and(current_entry->visibility,
	    expr);
}