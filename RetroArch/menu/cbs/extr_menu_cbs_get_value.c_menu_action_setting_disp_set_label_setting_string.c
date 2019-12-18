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
struct TYPE_10__ {char const* string; } ;
struct TYPE_9__ {TYPE_3__ target; } ;
struct TYPE_11__ {TYPE_2__ value; } ;
typedef  TYPE_4__ rarch_setting_t ;
struct TYPE_12__ {TYPE_1__* list; } ;
typedef  TYPE_5__ file_list_t ;
struct TYPE_8__ {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 TYPE_4__* menu_setting_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static void menu_action_setting_disp_set_label_setting_string(file_list_t* list,
      unsigned *w, unsigned type, unsigned i,
      const char *label,
      char *s, size_t len,
      const char *path,
      char *s2, size_t len2)
{
   rarch_setting_t *setting = menu_setting_find(list->list[i].label);

   *w = 19;

   if (setting->value.target.string)
      strlcpy(s, setting->value.target.string, len);

   strlcpy(s2, path, len2);
}