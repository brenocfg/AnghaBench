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
 int /*<<< orphan*/  RARCH_PATH_SUBSYSTEM ; 
 int /*<<< orphan*/  path_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_set_special (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pending_subsystem_ident ; 
 int /*<<< orphan*/  pending_subsystem_init ; 
 int /*<<< orphan*/  pending_subsystem_rom_num ; 
 int /*<<< orphan*/  pending_subsystem_roms ; 

void content_set_subsystem_info(void)
{
   if (!pending_subsystem_init)
      return;

   path_set(RARCH_PATH_SUBSYSTEM, pending_subsystem_ident);
   path_set_special(pending_subsystem_roms, pending_subsystem_rom_num);
}