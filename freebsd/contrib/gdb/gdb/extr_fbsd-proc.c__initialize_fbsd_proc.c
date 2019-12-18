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
 int /*<<< orphan*/  fbsd_find_memory_regions ; 
 int /*<<< orphan*/  fbsd_make_corefile_notes ; 

void
_initialize_fbsd_proc (void)
{
  extern void inftarg_set_find_memory_regions ();
  extern void inftarg_set_make_corefile_notes ();

  inftarg_set_find_memory_regions (fbsd_find_memory_regions);
  inftarg_set_make_corefile_notes (fbsd_make_corefile_notes);
}