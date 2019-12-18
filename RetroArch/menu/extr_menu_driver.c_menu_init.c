#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  bundle_assets_dst_subdir; int /*<<< orphan*/  bundle_assets_dst; int /*<<< orphan*/  bundle_assets_src; } ;
struct TYPE_9__ {scalar_t__ bundle_assets_extract_version_current; scalar_t__ bundle_assets_extract_last_version; } ;
struct TYPE_8__ {scalar_t__ bundle_assets_extract_enable; scalar_t__ config_save_on_exit; scalar_t__ menu_show_start_screen; } ;
struct TYPE_11__ {TYPE_3__ arrays; TYPE_2__ uints; TYPE_1__ bools; } ;
typedef  TYPE_4__ settings_t ;
typedef  int /*<<< orphan*/  menu_handle_t ;
struct TYPE_12__ {scalar_t__ allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_MENU_SAVE_CURRENT_CONFIG ; 
 int /*<<< orphan*/  MENU_DIALOG_HELP_EXTRACT ; 
 int /*<<< orphan*/  MENU_DIALOG_WELCOME ; 
 int /*<<< orphan*/  bundle_decompressed ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* config_get_ptr () ; 
 int /*<<< orphan*/  configuration_set_bool (TYPE_4__*,scalar_t__,int) ; 
 scalar_t__ menu_dialog_is_push_pending () ; 
 int /*<<< orphan*/  menu_dialog_push_pending (int,int /*<<< orphan*/ ) ; 
 TYPE_5__ menu_disp_ca ; 
 int /*<<< orphan*/  menu_display_has_windowed ; 
 int /*<<< orphan*/  menu_entries_init () ; 
 int /*<<< orphan*/  menu_input_reset () ; 
 int /*<<< orphan*/  menu_shader_manager_init () ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_push_decompress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_driver_has_windowed () ; 

__attribute__((used)) static bool menu_init(menu_handle_t *menu_data)
{
   settings_t *settings        = config_get_ptr();

   /* Ensure that menu pointer input is correctly
    * initialised */
   menu_input_reset();

   if (!menu_entries_init())
      return false;

   if (settings->bools.menu_show_start_screen)
   {
      /* We don't want the welcome dialog screen to show up
       * again after the first startup, so we save to config
       * file immediately. */

      menu_dialog_push_pending(true, MENU_DIALOG_WELCOME);

      configuration_set_bool(settings,
            settings->bools.menu_show_start_screen, false);
#if !(defined(PS2) && defined(DEBUG)) /* TODO: PS2 IMPROVEMENT */
      if (settings->bools.config_save_on_exit)
         command_event(CMD_EVENT_MENU_SAVE_CURRENT_CONFIG, NULL);
#endif
   }

   if (      settings->bools.bundle_assets_extract_enable
         && !string_is_empty(settings->arrays.bundle_assets_src)
         && !string_is_empty(settings->arrays.bundle_assets_dst)
#ifdef IOS
         && menu_dialog_is_push_pending()
#else
         && (settings->uints.bundle_assets_extract_version_current
            != settings->uints.bundle_assets_extract_last_version)
#endif
      )
   {
      menu_dialog_push_pending(true, MENU_DIALOG_HELP_EXTRACT);
#ifdef HAVE_COMPRESSION
      task_push_decompress(settings->arrays.bundle_assets_src,
            settings->arrays.bundle_assets_dst,
            NULL, settings->arrays.bundle_assets_dst_subdir,
            NULL, bundle_decompressed, NULL, NULL);
#endif
   }

#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
   menu_shader_manager_init();
#endif

   menu_disp_ca.allocated    =  0;

   menu_display_has_windowed = video_driver_has_windowed();

   return true;
}