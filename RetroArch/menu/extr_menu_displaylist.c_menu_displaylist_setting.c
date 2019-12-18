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
struct TYPE_5__ {int /*<<< orphan*/  add_empty_entry; int /*<<< orphan*/  parse_type; int /*<<< orphan*/  enum_idx; TYPE_1__* info; } ;
typedef  TYPE_2__ menu_displaylist_ctx_parse_entry_t ;
struct TYPE_4__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int menu_displaylist_parse_settings_enum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool menu_displaylist_setting(menu_displaylist_ctx_parse_entry_t *entry)
{
   if (menu_displaylist_parse_settings_enum(
            entry->info->list,
            entry->enum_idx,
            entry->parse_type,
            entry->add_empty_entry) == -1)
      return false;
   return true;
}