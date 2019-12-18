#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__* integer; } ;
struct TYPE_7__ {TYPE_1__ target; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* change_handler ) (TYPE_3__*) ;scalar_t__ offset_by; TYPE_2__ value; } ;
typedef  TYPE_3__ rarch_setting_t ;
typedef  scalar_t__ int32_t ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;

/* Variables and functions */
 int action_cancel_pop_default (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atoi (char const*) ; 
 TYPE_3__* menu_setting_find_enum (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static int action_ok_push_dropdown_setting_int_item_special(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   enum msg_hash_enums enum_idx = (enum msg_hash_enums)atoi(label);
   rarch_setting_t     *setting = menu_setting_find_enum(enum_idx);

   if (!setting)
      return -1;

   *setting->value.target.integer = (int32_t)(idx + setting->offset_by);

   if (setting->change_handler)
      setting->change_handler(setting);

   return action_cancel_pop_default(NULL, NULL, 0, 0);
}