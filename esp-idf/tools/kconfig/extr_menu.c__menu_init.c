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
struct TYPE_4__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 TYPE_1__* current_entry ; 
 TYPE_1__* current_menu ; 
 int /*<<< orphan*/ * last_entry_ptr ; 
 TYPE_1__ rootmenu ; 

void _menu_init(void)
{
	current_entry = current_menu = &rootmenu;
	last_entry_ptr = &rootmenu.list;
}