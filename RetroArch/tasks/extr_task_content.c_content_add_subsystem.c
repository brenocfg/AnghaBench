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
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  pending_subsystem_id ; 
 int /*<<< orphan*/  pending_subsystem_ident ; 
 size_t pending_subsystem_rom_id ; 
 char** pending_subsystem_roms ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

void content_add_subsystem(const char* path)
{
   size_t pending_size                              = PATH_MAX_LENGTH * sizeof(char);
   pending_subsystem_roms[pending_subsystem_rom_id] = (char*)malloc(pending_size);

   strlcpy(pending_subsystem_roms[pending_subsystem_rom_id], path, pending_size);
   RARCH_LOG("[subsystem] subsystem id: %d subsystem ident: %s rom id: %d, rom path: %s\n",
      pending_subsystem_id, pending_subsystem_ident, pending_subsystem_rom_id,
      pending_subsystem_roms[pending_subsystem_rom_id]);
   pending_subsystem_rom_id++;
}