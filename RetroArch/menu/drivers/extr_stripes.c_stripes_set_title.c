#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ categories_selection_ptr; scalar_t__ system_tab_end; int /*<<< orphan*/  title_name; int /*<<< orphan*/  horizontal_list; } ;
typedef  TYPE_1__ stripes_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  fill_pathname_base_noext (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  menu_entries_get_at_offset (int /*<<< orphan*/ ,scalar_t__,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_entries_get_title (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stripes_set_title(stripes_handle_t *stripes)
{
   if (stripes->categories_selection_ptr <= stripes->system_tab_end)
   {
      menu_entries_get_title(stripes->title_name, sizeof(stripes->title_name));
   }
   else
   {
      const char *path = NULL;
      menu_entries_get_at_offset(
            stripes->horizontal_list,
            stripes->categories_selection_ptr - (stripes->system_tab_end + 1),
            &path, NULL, NULL, NULL, NULL);

      if (!path)
         return;

      fill_pathname_base_noext(
            stripes->title_name, path, sizeof(stripes->title_name));
   }
}