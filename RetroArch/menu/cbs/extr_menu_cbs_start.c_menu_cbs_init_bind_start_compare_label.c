#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int enum_idx; } ;
typedef  TYPE_1__ menu_file_list_cbs_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_ACTION_START (TYPE_1__*,int /*<<< orphan*/ ) ; 
#define  MENU_ENUM_LABEL_CHEAT_NUM_PASSES 143 
#define  MENU_ENUM_LABEL_CORE_LIST 142 
#define  MENU_ENUM_LABEL_NETPLAY_MITM_SERVER 141 
#define  MENU_ENUM_LABEL_PLAYLIST_MANAGER_DEFAULT_CORE 140 
#define  MENU_ENUM_LABEL_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE 139 
#define  MENU_ENUM_LABEL_PLAYLIST_MANAGER_LEFT_THUMBNAIL_MODE 138 
#define  MENU_ENUM_LABEL_PLAYLIST_MANAGER_RIGHT_THUMBNAIL_MODE 137 
#define  MENU_ENUM_LABEL_REMAP_FILE_LOAD 136 
#define  MENU_ENUM_LABEL_SCREEN_RESOLUTION 135 
#define  MENU_ENUM_LABEL_SHADER_WATCH_FOR_CHANGES 134 
#define  MENU_ENUM_LABEL_VIDEO_FILTER 133 
#define  MENU_ENUM_LABEL_VIDEO_SHADER_FILTER_PASS 132 
#define  MENU_ENUM_LABEL_VIDEO_SHADER_NUM_PASSES 131 
#define  MENU_ENUM_LABEL_VIDEO_SHADER_PASS 130 
#define  MENU_ENUM_LABEL_VIDEO_SHADER_PRESET 129 
#define  MENU_ENUM_LABEL_VIDEO_SHADER_SCALE_PASS 128 
 int MSG_UNKNOWN ; 
 int /*<<< orphan*/  action_start_cheat_num_passes ; 
 int /*<<< orphan*/  action_start_load_core ; 
 int /*<<< orphan*/  action_start_netplay_mitm_server ; 
 int /*<<< orphan*/  action_start_playlist_association ; 
 int /*<<< orphan*/  action_start_playlist_label_display_mode ; 
 int /*<<< orphan*/  action_start_playlist_left_thumbnail_mode ; 
 int /*<<< orphan*/  action_start_playlist_right_thumbnail_mode ; 
 int /*<<< orphan*/  action_start_remap_file_load ; 
 int /*<<< orphan*/  action_start_shader_filter_pass ; 
 int /*<<< orphan*/  action_start_shader_num_passes ; 
 int /*<<< orphan*/  action_start_shader_pass ; 
 int /*<<< orphan*/  action_start_shader_preset ; 
 int /*<<< orphan*/  action_start_shader_scale_pass ; 
 int /*<<< orphan*/  action_start_shader_watch_for_changes ; 
 int /*<<< orphan*/  action_start_video_filter_file_load ; 
 int /*<<< orphan*/  action_start_video_resolution ; 

__attribute__((used)) static int menu_cbs_init_bind_start_compare_label(menu_file_list_cbs_t *cbs)
{
   if (cbs->enum_idx != MSG_UNKNOWN)
   {
      switch (cbs->enum_idx)
      {
         case MENU_ENUM_LABEL_CORE_LIST:
            BIND_ACTION_START(cbs, action_start_load_core);
            break;
         case MENU_ENUM_LABEL_VIDEO_SHADER_PRESET:
            BIND_ACTION_START(cbs, action_start_shader_preset);
            break;
         case MENU_ENUM_LABEL_REMAP_FILE_LOAD:
            BIND_ACTION_START(cbs, action_start_remap_file_load);
            break;
         case MENU_ENUM_LABEL_VIDEO_FILTER:
            BIND_ACTION_START(cbs, action_start_video_filter_file_load);
            break;
         case MENU_ENUM_LABEL_VIDEO_SHADER_PASS:
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
            BIND_ACTION_START(cbs, action_start_shader_pass);
#endif
            break;
         case MENU_ENUM_LABEL_VIDEO_SHADER_SCALE_PASS:
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
            BIND_ACTION_START(cbs, action_start_shader_scale_pass);
#endif
            break;
         case MENU_ENUM_LABEL_VIDEO_SHADER_FILTER_PASS:
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
            BIND_ACTION_START(cbs, action_start_shader_filter_pass);
#endif
            break;
         case MENU_ENUM_LABEL_SHADER_WATCH_FOR_CHANGES:
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
            BIND_ACTION_START(cbs, action_start_shader_watch_for_changes);
#endif
            break;
         case MENU_ENUM_LABEL_VIDEO_SHADER_NUM_PASSES:
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
            BIND_ACTION_START(cbs, action_start_shader_num_passes);
#endif
            break;
         case MENU_ENUM_LABEL_CHEAT_NUM_PASSES:
            BIND_ACTION_START(cbs, action_start_cheat_num_passes);
            break;
         case MENU_ENUM_LABEL_SCREEN_RESOLUTION:
            BIND_ACTION_START(cbs, action_start_video_resolution);
            break;
         case MENU_ENUM_LABEL_NETPLAY_MITM_SERVER:
            BIND_ACTION_START(cbs, action_start_netplay_mitm_server);
            break;
         case MENU_ENUM_LABEL_PLAYLIST_MANAGER_DEFAULT_CORE:
            BIND_ACTION_START(cbs, action_start_playlist_association);
            break;
         case MENU_ENUM_LABEL_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE:
            BIND_ACTION_START(cbs, action_start_playlist_label_display_mode);
            break;
         case MENU_ENUM_LABEL_PLAYLIST_MANAGER_RIGHT_THUMBNAIL_MODE:
            BIND_ACTION_START(cbs, action_start_playlist_right_thumbnail_mode);
            break;
         case MENU_ENUM_LABEL_PLAYLIST_MANAGER_LEFT_THUMBNAIL_MODE:
            BIND_ACTION_START(cbs, action_start_playlist_left_thumbnail_mode);
            break;
         default:
            return -1;
      }
   }

   return 0;
}