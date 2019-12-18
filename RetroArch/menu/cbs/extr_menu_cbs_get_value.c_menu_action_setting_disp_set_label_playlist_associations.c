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
typedef  int /*<<< orphan*/  playlist_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NOT_AVAILABLE ; 
 char const* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 char* playlist_get_default_core_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  string_is_equal (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static void menu_action_setting_disp_set_label_playlist_associations(file_list_t* list,
      unsigned *w, unsigned type, unsigned i,
      const char *label,
      char *s, size_t len,
      const char *path,
      char *s2, size_t len2)
{
   playlist_t *playlist  = playlist_get_cached();
   const char *core_name = NULL;

   *s = '\0';
   *w = 19;

   strlcpy(s2, path, len2);

   if (!playlist)
      return;

   core_name = playlist_get_default_core_name(playlist);

   if (!string_is_empty(core_name) &&
       !string_is_equal(core_name, "DETECT"))
      strlcpy(s, core_name, len);
   else
      strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NOT_AVAILABLE), len);
}