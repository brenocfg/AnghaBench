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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  menu_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ACTION_START ; 
 int /*<<< orphan*/  menu_entry_action (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_entry_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  menu_entry_init (int /*<<< orphan*/ *) ; 

void menu_entry_reset(uint32_t i)
{
   menu_entry_t entry;

   menu_entry_init(&entry);
   menu_entry_get(&entry, 0, i, NULL, true);

   menu_entry_action(&entry, (size_t)i, MENU_ACTION_START);
}