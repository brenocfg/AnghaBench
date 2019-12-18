#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_3__* horizontal_list; } ;
typedef  TYPE_4__ xmb_handle_t ;
struct TYPE_15__ {scalar_t__ menu_content_show_playlists; } ;
struct TYPE_14__ {char* directory_playlist; } ;
struct TYPE_18__ {TYPE_2__ bools; TYPE_1__ paths; } ;
typedef  TYPE_5__ settings_t ;
struct TYPE_19__ {void* path; int /*<<< orphan*/  enum_idx; int /*<<< orphan*/  type_default; void* exts; void* label; TYPE_3__* list; } ;
typedef  TYPE_6__ menu_displaylist_info_t ;
struct TYPE_16__ {size_t size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLIST_DATABASE_PLAYLISTS_HORIZONTAL ; 
 int /*<<< orphan*/  FILE_TYPE_PLAIN ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_PLAYLISTS_TAB ; 
 TYPE_5__* config_get_ptr () ; 
 scalar_t__ menu_displaylist_ctl (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  menu_displaylist_info_free (TYPE_6__*) ; 
 int /*<<< orphan*/  menu_displaylist_info_init (TYPE_6__*) ; 
 int /*<<< orphan*/  menu_displaylist_process (TYPE_6__*) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  string_is_empty (void*) ; 
 int /*<<< orphan*/  xmb_node_allocate_userdata (TYPE_4__*,unsigned int) ; 

__attribute__((used)) static void xmb_init_horizontal_list(xmb_handle_t *xmb)
{
   menu_displaylist_info_t info;
   settings_t *settings         = config_get_ptr();

   menu_displaylist_info_init(&info);

   info.list                    = xmb->horizontal_list;
   info.path                    = strdup(
         settings->paths.directory_playlist);
   info.label                   = strdup(
         msg_hash_to_str(MENU_ENUM_LABEL_PLAYLISTS_TAB));
   info.exts                    = strdup("lpl");
   info.type_default            = FILE_TYPE_PLAIN;
   info.enum_idx                = MENU_ENUM_LABEL_PLAYLISTS_TAB;

   if (settings->bools.menu_content_show_playlists && !string_is_empty(info.path))
   {
      if (menu_displaylist_ctl(DISPLAYLIST_DATABASE_PLAYLISTS_HORIZONTAL, &info))
      {
         size_t i;
         for (i = 0; i < xmb->horizontal_list->size; i++)
            xmb_node_allocate_userdata(xmb, (unsigned)i);
         menu_displaylist_process(&info);
      }
   }

   menu_displaylist_info_free(&info);
}