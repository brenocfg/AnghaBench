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
 unsigned int RARCH_MAX_SUBSYSTEM_ROMS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int pending_subsystem_init ; 
 scalar_t__ pending_subsystem_rom_id ; 
 int /*<<< orphan*/ ** pending_subsystem_roms ; 

void content_clear_subsystem(void)
{
   unsigned i;

   pending_subsystem_rom_id = 0;
   pending_subsystem_init   = false;

   for (i = 0; i < RARCH_MAX_SUBSYSTEM_ROMS; i++)
   {
      if (pending_subsystem_roms[i])
      {
         free(pending_subsystem_roms[i]);
         pending_subsystem_roms[i] = NULL;
      }
   }
}