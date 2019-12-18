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
struct TYPE_4__ {int /*<<< orphan*/  cheevos_hardcore_mode_enable; int /*<<< orphan*/  cheevos_enable; } ;
struct TYPE_5__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_NETPLAY_INIT ; 
 scalar_t__ CORE_TYPE_DUMMY ; 
 scalar_t__ CORE_TYPE_PLAIN ; 
 int /*<<< orphan*/  MSG_SKIPPING_SRAM_LOAD ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsv_movie_deinit () ; 
 int /*<<< orphan*/  bsv_movie_init () ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  command_event_load_auto_state () ; 
 int /*<<< orphan*/  command_event_set_savestate_auto_index () ; 
 TYPE_2__* configuration_settings ; 
 int /*<<< orphan*/  content_get_status (int*,int*) ; 
 int /*<<< orphan*/  content_init () ; 
 int /*<<< orphan*/  content_set_subsystem_info () ; 
 scalar_t__ current_core_type ; 
 scalar_t__ event_load_save_files () ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_fill_names () ; 
 int rarch_use_sram ; 
 int runloop_core_running ; 

__attribute__((used)) static bool event_init_content(void)
{
   bool contentless = false;
   bool is_inited   = false;

   content_get_status(&contentless, &is_inited);

   rarch_use_sram   = (current_core_type == CORE_TYPE_PLAIN)
      && !contentless;

   /* No content to be loaded for dummy core,
    * just successfully exit. */
   if (current_core_type == CORE_TYPE_DUMMY)
      return true;

   content_set_subsystem_info();

   content_get_status(&contentless, &is_inited);

   if (!contentless)
      path_fill_names();

   if (!content_init())
   {
      runloop_core_running = false;
      return false;
   }

   command_event_set_savestate_auto_index();

   if (event_load_save_files())
      RARCH_LOG("%s.\n",
            msg_hash_to_str(MSG_SKIPPING_SRAM_LOAD));

/*
   Since the operations are asynchronous we can't
   guarantee users will not use auto_load_state to cheat on
   achievements so we forbid auto_load_state from happening
   if cheevos_enable and cheevos_hardcode_mode_enable
   are true.
*/
#ifdef HAVE_CHEEVOS
   {
      settings_t *settings = configuration_settings;
      if (  !settings->bools.cheevos_enable ||
            !settings->bools.cheevos_hardcore_mode_enable)
         command_event_load_auto_state();
   }
#else
   command_event_load_auto_state();
#endif

   bsv_movie_deinit();
   bsv_movie_init();
   command_event(CMD_EVENT_NETPLAY_INIT, NULL);

   return true;
}