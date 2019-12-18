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
struct TYPE_5__ {TYPE_1__* list; } ;
typedef  TYPE_2__ file_list_t ;
struct TYPE_4__ {char* alt; char* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static void menu_action_setting_disp_set_label_entry_url(
      file_list_t* list,
      unsigned *w, unsigned type, unsigned i,
      const char *label,
      char *s, size_t len,
      const char *path,
      char *s2, size_t len2)
{
   const char *representation_label = list->list[i].alt
      ? list->list[i].alt
      : list->list[i].path;
   *s = '\0';
   *w = 8;

   if (!string_is_empty(representation_label))
      strlcpy(s2, representation_label, len2);
   else
      strlcpy(s2, path, len2);
}