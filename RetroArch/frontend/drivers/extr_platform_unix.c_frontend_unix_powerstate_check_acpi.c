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
struct RDIR {int dummy; } ;
typedef  enum frontend_powerstate { ____Placeholder_frontend_powerstate } frontend_powerstate ;

/* Variables and functions */
 int FRONTEND_POWERSTATE_CHARGED ; 
 int FRONTEND_POWERSTATE_CHARGING ; 
 int FRONTEND_POWERSTATE_NO_SOURCE ; 
 int FRONTEND_POWERSTATE_ON_POWER_SOURCE ; 
 int /*<<< orphan*/  check_proc_acpi_ac_adapter (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  check_proc_acpi_battery (int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  proc_acpi_ac_adapter_path ; 
 int /*<<< orphan*/  proc_acpi_battery_path ; 
 int /*<<< orphan*/  retro_closedir (struct RDIR*) ; 
 scalar_t__ retro_dirent_error (struct RDIR*) ; 
 int /*<<< orphan*/  retro_dirent_get_name (struct RDIR*) ; 
 struct RDIR* retro_opendir (int /*<<< orphan*/ ) ; 
 scalar_t__ retro_readdir (struct RDIR*) ; 

__attribute__((used)) static bool frontend_unix_powerstate_check_acpi(
      enum frontend_powerstate *state,
      int *seconds, int *percent)
{
   bool have_battery   = false;
   bool have_ac        = false;
   bool charging       = false;
   struct RDIR *entry  = retro_opendir(proc_acpi_battery_path);
   if (!entry)
      return false;

   if (retro_dirent_error(entry))
   {
      retro_closedir(entry);
      return false;
   }

   while (retro_readdir(entry))
      check_proc_acpi_battery(retro_dirent_get_name(entry),
            &have_battery, &charging, seconds, percent);

   retro_closedir(entry);

   entry = retro_opendir(proc_acpi_ac_adapter_path);
   if (!entry)
      return false;

   while (retro_readdir(entry))
      check_proc_acpi_ac_adapter(
            retro_dirent_get_name(entry), &have_ac);

   retro_closedir(entry);

   if (!have_battery)
      *state = FRONTEND_POWERSTATE_NO_SOURCE;
   else if (charging)
      *state = FRONTEND_POWERSTATE_CHARGING;
   else if (have_ac)
      *state = FRONTEND_POWERSTATE_CHARGED;
   else
      *state = FRONTEND_POWERSTATE_ON_POWER_SOURCE;

   return true;
}