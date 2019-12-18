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
struct retro_subsystem_info {int /*<<< orphan*/  desc; int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char const*) ; 

const struct retro_subsystem_info *libretro_find_subsystem_info(
      const struct retro_subsystem_info *info, unsigned num_info,
      const char *ident)
{
   unsigned i;
   for (i = 0; i < num_info; i++)
   {
      if (string_is_equal(info[i].ident, ident))
         return &info[i];
      else if (string_is_equal(info[i].desc, ident))
         return &info[i];
   }

   return NULL;
}