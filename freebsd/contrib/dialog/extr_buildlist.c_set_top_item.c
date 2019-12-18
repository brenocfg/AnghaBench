#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* list; } ;
struct TYPE_4__ {int top_index; } ;
typedef  TYPE_2__ ALL_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  DLG_TRACE (char*) ; 
 int /*<<< orphan*/  mySide (int) ; 

__attribute__((used)) static void
set_top_item(ALL_DATA * all, int choice, int selected)
{
    if (choice != all->list[selected].top_index) {
	DLG_TRACE(("# set top of %s column to %d\n",
		   mySide(selected),
		   choice));
	all->list[selected].top_index = choice;
    }
}