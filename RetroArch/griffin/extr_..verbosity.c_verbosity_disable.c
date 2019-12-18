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
 int /*<<< orphan*/  frontend_driver_detach_console () ; 
 int /*<<< orphan*/  log_file_initialized ; 
 int main_verbosity ; 

void verbosity_disable(void)
{
   main_verbosity = false;
#ifdef RARCH_INTERNAL
   if (!log_file_initialized)
      frontend_driver_detach_console();
#endif
}