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

/* Variables and functions */
 int /*<<< orphan*/  RARCH_CTL_CORE_OPTIONS_DEINIT ; 
 int camera_driver_active ; 
 int core_set_shared_context ; 
 int /*<<< orphan*/  dylib_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lib_handle ; 
 int location_driver_active ; 
 int /*<<< orphan*/  memset (struct retro_core_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  performance_counters_clear () ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  retroarch_frame_time_free () ; 
 int /*<<< orphan*/  retroarch_system_info_free () ; 

__attribute__((used)) static void uninit_libretro_symbols(struct retro_core_t *current_core)
{
#ifdef HAVE_DYNAMIC
   if (lib_handle)
      dylib_close(lib_handle);
   lib_handle = NULL;
#endif

   memset(current_core, 0, sizeof(struct retro_core_t));

   core_set_shared_context = false;

   rarch_ctl(RARCH_CTL_CORE_OPTIONS_DEINIT, NULL);
   retroarch_system_info_free();
   retroarch_frame_time_free();
   camera_driver_active      = false;
   location_driver_active    = false;

   /* Performance counters no longer valid. */
   performance_counters_clear();
}