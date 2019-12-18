#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int symbols_inited; int /*<<< orphan*/  (* retro_deinit ) () ;scalar_t__ inited; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVERS_CMD_ALL ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  command_event_disable_overrides () ; 
 int /*<<< orphan*/  core_unload_game () ; 
 TYPE_1__ current_core ; 
 int /*<<< orphan*/  driver_uninit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_remapping_set_defaults (int) ; 
 int /*<<< orphan*/  rcheevos_unload () ; 
 int /*<<< orphan*/  retroarch_unset_runtime_shader_preset () ; 
 scalar_t__ runloop_remaps_content_dir_active ; 
 scalar_t__ runloop_remaps_core_active ; 
 scalar_t__ runloop_remaps_game_active ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  uninit_libretro_symbols (TYPE_1__*) ; 
 int /*<<< orphan*/  video_driver_set_cached_frame_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void command_event_deinit_core(bool reinit)
{
#ifdef HAVE_CHEEVOS
   rcheevos_unload();
#endif

   RARCH_LOG("Unloading game..\n");
   core_unload_game();

   RARCH_LOG("Unloading core..\n");

   video_driver_set_cached_frame_ptr(NULL);

   if (current_core.inited)
      current_core.retro_deinit();

   RARCH_LOG("Unloading core symbols..\n");
   uninit_libretro_symbols(&current_core);
   current_core.symbols_inited = false;

   if (reinit)
      driver_uninit(DRIVERS_CMD_ALL);

   command_event_disable_overrides();
   retroarch_unset_runtime_shader_preset();

   if (     runloop_remaps_core_active
         || runloop_remaps_content_dir_active
         || runloop_remaps_game_active
      )
      input_remapping_set_defaults(true);
}