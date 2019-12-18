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
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  menu_entries_get_at_offset (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void menu_action_setting_disp_set_label_menu_file_core(
      file_list_t* list,
      unsigned *w, unsigned type, unsigned i,
      const char *label,
      char *s, size_t len,
      const char *path,
      char *s2, size_t len2)
{
   const char *alt = NULL;
   strlcpy(s, "(CORE)", len);

   menu_entries_get_at_offset(list, i, NULL,
         NULL, NULL, NULL, &alt);

   *w = (unsigned)strlen(s);
   if (alt)
      strlcpy(s2, alt, len2);
}