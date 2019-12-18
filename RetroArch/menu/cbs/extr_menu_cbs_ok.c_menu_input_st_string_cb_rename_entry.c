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
struct playlist_entry {char* label; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  command_playlist_update_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct playlist_entry*) ; 
 int /*<<< orphan*/  menu_input_dialog_end () ; 
 char* menu_input_dialog_get_buffer () ; 
 int /*<<< orphan*/  menu_input_dialog_get_kb_idx () ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 

__attribute__((used)) static void menu_input_st_string_cb_rename_entry(void *userdata,
      const char *str)
{
   if (str && *str)
   {
      const char        *label    = menu_input_dialog_get_buffer();

      if (!string_is_empty(label))
      {
         struct playlist_entry entry = {0};

         /* the update function reads our entry as const, so these casts are safe */
         entry.label = (char*)label;

         command_playlist_update_write(NULL,
               menu_input_dialog_get_kb_idx(),
               &entry);
      }
   }

   menu_input_dialog_end();
}