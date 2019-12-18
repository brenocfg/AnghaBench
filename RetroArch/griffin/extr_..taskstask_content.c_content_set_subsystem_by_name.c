#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct retro_subsystem_info {int /*<<< orphan*/  ident; } ;
struct TYPE_4__ {struct retro_subsystem_info* data; } ;
struct TYPE_5__ {TYPE_1__ subsystem; } ;
typedef  TYPE_2__ rarch_system_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  content_set_subsystem (unsigned int) ; 
 TYPE_2__* runloop_get_system_info () ; 
 scalar_t__ string_is_equal (char const*,int /*<<< orphan*/ ) ; 
 unsigned int subsystem_current_count ; 
 struct retro_subsystem_info* subsystem_data ; 

bool content_set_subsystem_by_name(const char* subsystem_name)
{
   rarch_system_info_t                  *system = runloop_get_system_info();
   const struct retro_subsystem_info *subsystem;
   unsigned i = 0;

   /* Core fully loaded, use the subsystem data */
   if (system->subsystem.data)
      subsystem = system->subsystem.data;
   /* Core not loaded completely, use the data we peeked on load core */
   else
      subsystem = subsystem_data;

   for (i = 0; i < subsystem_current_count; i++, subsystem++)
   {
      if (string_is_equal(subsystem_name, subsystem->ident))
      {
         content_set_subsystem(i);
         return true;
      }
   }

   return false;
}