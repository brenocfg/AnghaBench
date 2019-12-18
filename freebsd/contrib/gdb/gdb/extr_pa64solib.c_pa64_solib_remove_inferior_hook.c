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
struct TYPE_2__ {int /*<<< orphan*/  dld_flags; int /*<<< orphan*/  dld_flags_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_HP_DEBUG_CALLBACK ; 
 TYPE_1__ dld_cache ; 
 int /*<<< orphan*/  target_write_memory (int /*<<< orphan*/ ,char*,int) ; 

void
pa64_solib_remove_inferior_hook (int pid)
{
  /* Turn off the DT_HP_DEBUG_CALLBACK bit in the dynamic linker flags.  */
  dld_cache.dld_flags &= ~DT_HP_DEBUG_CALLBACK;
  target_write_memory (dld_cache.dld_flags_addr,
		       (char *)&dld_cache.dld_flags,
		       sizeof (dld_cache.dld_flags));
}