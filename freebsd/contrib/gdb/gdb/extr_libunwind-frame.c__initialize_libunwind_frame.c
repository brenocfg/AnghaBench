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
 int /*<<< orphan*/  libunwind_descr_handle ; 
 int /*<<< orphan*/  libunwind_descr_init ; 
 int /*<<< orphan*/  libunwind_initialized ; 
 int /*<<< orphan*/  libunwind_load () ; 
 int /*<<< orphan*/  register_gdbarch_data (int /*<<< orphan*/ ) ; 

void
_initialize_libunwind_frame (void)
{
  libunwind_descr_handle = register_gdbarch_data (libunwind_descr_init);

  libunwind_initialized = libunwind_load ();
}