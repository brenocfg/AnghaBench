#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  rarch_setting_t ;
struct TYPE_6__ {int /*<<< orphan*/ * setting; } ;
typedef  TYPE_2__ menu_file_list_cbs_t ;
struct TYPE_7__ {TYPE_1__* list; } ;
typedef  TYPE_3__ file_list_t ;
struct TYPE_5__ {scalar_t__ actiondata; } ;

/* Variables and functions */
 TYPE_3__* menu_entries_get_selection_buf_ptr_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setting_set_with_string_representation (int /*<<< orphan*/ *,char const*) ; 

void menu_entry_set_value(uint32_t i, const char *s)
{
   file_list_t *selection_buf    = menu_entries_get_selection_buf_ptr_internal(0);
   menu_file_list_cbs_t *cbs     = selection_buf ?
      (menu_file_list_cbs_t*)selection_buf->list[i].actiondata : NULL;
   rarch_setting_t *setting      = cbs ? cbs->setting : NULL;
   setting_set_with_string_representation(setting, s);
}