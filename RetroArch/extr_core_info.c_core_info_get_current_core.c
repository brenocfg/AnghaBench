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
typedef  int /*<<< orphan*/  core_info_t ;

/* Variables and functions */
 int /*<<< orphan*/ * core_info_current ; 

bool core_info_get_current_core(core_info_t **core)
{
   if (!core)
      return false;
   *core = core_info_current;
   return true;
}