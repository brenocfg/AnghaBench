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
 int /*<<< orphan*/ * core_info_current ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void core_info_free_current_core(void)
{
   if (core_info_current)
      free(core_info_current);
   core_info_current = NULL;
}