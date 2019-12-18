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

/* Variables and functions */
 int /*<<< orphan*/  retro_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_new () ; 
 int /*<<< orphan*/  task_save_files ; 

void path_init_savefile_new(void)
{
   task_save_files = string_list_new();
   retro_assert(task_save_files);
}