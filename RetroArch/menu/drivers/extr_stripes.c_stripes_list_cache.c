#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {size_t selection_ptr_old; size_t system_tab_end; size_t categories_selection_ptr_old; size_t categories_selection_ptr; unsigned int categories_active_idx; int /*<<< orphan*/  selection_buf_old; } ;
typedef  TYPE_3__ stripes_handle_t ;
struct TYPE_13__ {scalar_t__ menu_horizontal_animation; } ;
struct TYPE_16__ {TYPE_1__ bools; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_17__ {size_t size; TYPE_2__* list; } ;
typedef  TYPE_5__ file_list_t ;
typedef  enum menu_list_type { ____Placeholder_menu_list_type } menu_list_type ;
struct TYPE_14__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * label; } ;

/* Variables and functions */
#define  MENU_ACTION_LEFT 139 
 int /*<<< orphan*/  MENU_ADD_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_ADD_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_FAVORITES_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_HISTORY_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_HORIZONTAL_MENU ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_IMAGES_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_MAIN_MENU ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_MUSIC_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_NETPLAY_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_SETTINGS_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VIDEO_TAB ; 
 int /*<<< orphan*/  MENU_FAVORITES_TAB ; 
 int /*<<< orphan*/  MENU_HISTORY_TAB ; 
 int /*<<< orphan*/  MENU_IMAGES_TAB ; 
#define  MENU_LIST_HORIZONTAL 138 
#define  MENU_LIST_PLAIN 137 
 int /*<<< orphan*/  MENU_MUSIC_TAB ; 
 int /*<<< orphan*/  MENU_NETPLAY_TAB ; 
 int /*<<< orphan*/  MENU_SETTINGS ; 
 int /*<<< orphan*/  MENU_SETTINGS_TAB ; 
 int /*<<< orphan*/  MENU_SETTING_HORIZONTAL_MENU ; 
 int /*<<< orphan*/  MENU_VIDEO_TAB ; 
#define  STRIPES_SYSTEM_TAB_ADD 136 
#define  STRIPES_SYSTEM_TAB_FAVORITES 135 
#define  STRIPES_SYSTEM_TAB_HISTORY 134 
#define  STRIPES_SYSTEM_TAB_IMAGES 133 
#define  STRIPES_SYSTEM_TAB_MAIN 132 
#define  STRIPES_SYSTEM_TAB_MUSIC 131 
#define  STRIPES_SYSTEM_TAB_NETPLAY 130 
#define  STRIPES_SYSTEM_TAB_SETTINGS 129 
#define  STRIPES_SYSTEM_TAB_VIDEO 128 
 TYPE_4__* config_get_ptr () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_5__* menu_entries_get_menu_stack_ptr (int /*<<< orphan*/ ) ; 
 TYPE_5__* menu_entries_get_selection_buf_ptr (int /*<<< orphan*/ ) ; 
 size_t menu_navigation_get_selection () ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 void* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripes_calculate_visible_range (TYPE_3__*,unsigned int,size_t,size_t,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  stripes_get_system_tab (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  stripes_list_deep_copy (TYPE_5__*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 size_t stripes_list_get_size (TYPE_3__*,int) ; 
 int /*<<< orphan*/  video_driver_get_size (int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static void stripes_list_cache(void *data, enum menu_list_type type, unsigned action)
{
   size_t stack_size, list_size;
   stripes_handle_t      *stripes     = (stripes_handle_t*)data;
   file_list_t *menu_stack    = menu_entries_get_menu_stack_ptr(0);
   file_list_t *selection_buf = menu_entries_get_selection_buf_ptr(0);
   size_t selection           = menu_navigation_get_selection();
   settings_t *settings       = config_get_ptr();

   if (!stripes)
      return;

   /* Check whether to enable the horizontal animation. */
   if (settings->bools.menu_horizontal_animation)
   {
      unsigned first = 0, last = 0;
      unsigned height = 0;
      video_driver_get_size(NULL, &height);

      /* FIXME: this shouldn't be happening at all */
      if (selection >= selection_buf->size)
         selection = selection_buf->size ? selection_buf->size - 1 : 0;

      stripes->selection_ptr_old = selection;

      stripes_calculate_visible_range(stripes, height, selection_buf->size,
            stripes->selection_ptr_old, &first, &last);

      stripes_list_deep_copy(selection_buf, stripes->selection_buf_old, first, last);

      stripes->selection_ptr_old -= first;
      last                   -= first;
      first                   = 0;
   }
   else
      stripes->selection_ptr_old = 0;

   list_size = stripes_list_get_size(stripes, MENU_LIST_HORIZONTAL)
      + stripes->system_tab_end;

   switch (type)
   {
      case MENU_LIST_PLAIN:
         break;
      case MENU_LIST_HORIZONTAL:
         stripes->categories_selection_ptr_old = stripes->categories_selection_ptr;

         switch (action)
         {
            case MENU_ACTION_LEFT:
               if (stripes->categories_selection_ptr == 0)
               {
                  stripes->categories_selection_ptr = list_size;
                  stripes->categories_active_idx    = (unsigned)(list_size - 1);
               }
               else
                  stripes->categories_selection_ptr--;
               break;
            default:
               if (stripes->categories_selection_ptr == list_size)
               {
                  stripes->categories_selection_ptr = 0;
                  stripes->categories_active_idx = 1;
               }
               else
                  stripes->categories_selection_ptr++;
               break;
         }

         stack_size = menu_stack->size;

         if (menu_stack->list[stack_size - 1].label)
            free(menu_stack->list[stack_size - 1].label);
         menu_stack->list[stack_size - 1].label = NULL;

         switch (stripes_get_system_tab(stripes, (unsigned)stripes->categories_selection_ptr))
         {
            case STRIPES_SYSTEM_TAB_MAIN:
               menu_stack->list[stack_size - 1].label =
                  strdup(msg_hash_to_str(MENU_ENUM_LABEL_MAIN_MENU));
               menu_stack->list[stack_size - 1].type =
                  MENU_SETTINGS;
               break;
            case STRIPES_SYSTEM_TAB_SETTINGS:
               menu_stack->list[stack_size - 1].label =
                  strdup(msg_hash_to_str(MENU_ENUM_LABEL_SETTINGS_TAB));
               menu_stack->list[stack_size - 1].type =
                  MENU_SETTINGS_TAB;
               break;
#ifdef HAVE_IMAGEVIEWER
            case STRIPES_SYSTEM_TAB_IMAGES:
               menu_stack->list[stack_size - 1].label =
                  strdup(msg_hash_to_str(MENU_ENUM_LABEL_IMAGES_TAB));
               menu_stack->list[stack_size - 1].type =
                  MENU_IMAGES_TAB;
               break;
#endif
            case STRIPES_SYSTEM_TAB_MUSIC:
               menu_stack->list[stack_size - 1].label =
                  strdup(msg_hash_to_str(MENU_ENUM_LABEL_MUSIC_TAB));
               menu_stack->list[stack_size - 1].type =
                  MENU_MUSIC_TAB;
               break;
#ifdef HAVE_FFMPEG
            case STRIPES_SYSTEM_TAB_VIDEO:
               menu_stack->list[stack_size - 1].label =
                  strdup(msg_hash_to_str(MENU_ENUM_LABEL_VIDEO_TAB));
               menu_stack->list[stack_size - 1].type =
                  MENU_VIDEO_TAB;
               break;
#endif
            case STRIPES_SYSTEM_TAB_HISTORY:
               menu_stack->list[stack_size - 1].label =
                  strdup(msg_hash_to_str(MENU_ENUM_LABEL_HISTORY_TAB));
               menu_stack->list[stack_size - 1].type =
                  MENU_HISTORY_TAB;
               break;
            case STRIPES_SYSTEM_TAB_FAVORITES:
               menu_stack->list[stack_size - 1].label =
                  strdup(msg_hash_to_str(MENU_ENUM_LABEL_FAVORITES_TAB));
               menu_stack->list[stack_size - 1].type =
                  MENU_FAVORITES_TAB;
               break;
#ifdef HAVE_NETWORKING
            case STRIPES_SYSTEM_TAB_NETPLAY:
               menu_stack->list[stack_size - 1].label =
                  strdup(msg_hash_to_str(MENU_ENUM_LABEL_NETPLAY_TAB));
               menu_stack->list[stack_size - 1].type =
                  MENU_NETPLAY_TAB;
               break;
#endif
            case STRIPES_SYSTEM_TAB_ADD:
               menu_stack->list[stack_size - 1].label =
                  strdup(msg_hash_to_str(MENU_ENUM_LABEL_ADD_TAB));
               menu_stack->list[stack_size - 1].type =
                  MENU_ADD_TAB;
               break;
            default:
               menu_stack->list[stack_size - 1].label =
                  strdup(msg_hash_to_str(MENU_ENUM_LABEL_HORIZONTAL_MENU));
               menu_stack->list[stack_size - 1].type =
                  MENU_SETTING_HORIZONTAL_MENU;
               break;
         }
         break;
      default:
         break;
   }
}