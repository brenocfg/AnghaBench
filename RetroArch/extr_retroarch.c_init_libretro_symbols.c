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
struct retro_core_t {int dummy; } ;
typedef  enum rarch_core_type { ____Placeholder_rarch_core_type } rarch_core_type ;

/* Variables and functions */
 int /*<<< orphan*/  init_libretro_symbols_custom (int,struct retro_core_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int last_core_type ; 

__attribute__((used)) static bool init_libretro_symbols(enum rarch_core_type type,
      struct retro_core_t *current_core)
{
   /* Load symbols */
   if (!init_libretro_symbols_custom(type, current_core, NULL, NULL))
      return false;

#ifdef HAVE_RUNAHEAD
   /* remember last core type created, so creating a
    * secondary core will know what core type to use. */
   last_core_type = type;
#endif
   return true;
}