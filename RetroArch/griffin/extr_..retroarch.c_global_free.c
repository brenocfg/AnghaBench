#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct global {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  remapfile; } ;
struct TYPE_7__ {TYPE_1__ name; } ;
typedef  TYPE_2__ global_t ;
struct TYPE_8__ {int has_set_input_descriptors; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_LOG_FILE_DEINIT ; 
 int /*<<< orphan*/  CMD_EVENT_RECORD_DEINIT ; 
 int /*<<< orphan*/  RARCH_CTL_UNSET_BPS_PREF ; 
 int /*<<< orphan*/  RARCH_CTL_UNSET_IPS_PREF ; 
 int /*<<< orphan*/  RARCH_CTL_UNSET_UPS_PREF ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  content_deinit () ; 
 TYPE_5__ current_core ; 
 int /*<<< orphan*/  dir_clear_all () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_2__ g_extern ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  path_clear_all () ; 
 int /*<<< orphan*/  path_deinit_subsystem () ; 
 int rarch_block_config_read ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rarch_is_sram_load_disabled ; 
 int rarch_is_sram_save_disabled ; 
 int rarch_patch_blocked ; 
 int rarch_use_sram ; 
 int /*<<< orphan*/  retroarch_override_setting_free_state () ; 
 int runloop_overrides_active ; 
 int runloop_remaps_content_dir_active ; 
 int runloop_remaps_core_active ; 
 int runloop_remaps_game_active ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void global_free(void)
{
   global_t *global = NULL;

   content_deinit();

   path_deinit_subsystem();
   command_event(CMD_EVENT_RECORD_DEINIT, NULL);
   command_event(CMD_EVENT_LOG_FILE_DEINIT, NULL);

   rarch_block_config_read               = false;
   rarch_is_sram_load_disabled           = false;
   rarch_is_sram_save_disabled           = false;
   rarch_use_sram                        = false;
   rarch_ctl(RARCH_CTL_UNSET_BPS_PREF, NULL);
   rarch_ctl(RARCH_CTL_UNSET_IPS_PREF, NULL);
   rarch_ctl(RARCH_CTL_UNSET_UPS_PREF, NULL);
   rarch_patch_blocked                   = false;
   runloop_overrides_active              = false;
   runloop_remaps_core_active            = false;
   runloop_remaps_game_active            = false;
   runloop_remaps_content_dir_active     = false;

   current_core.has_set_input_descriptors = false;

   global = &g_extern;
   path_clear_all();
   dir_clear_all();

   if (global)
   {
      if (!string_is_empty(global->name.remapfile))
         free(global->name.remapfile);
      memset(global, 0, sizeof(struct global));
   }
   retroarch_override_setting_free_state();
}