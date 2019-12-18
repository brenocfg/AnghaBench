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
struct TYPE_6__ {unsigned int* unsigned_integer; } ;
struct TYPE_7__ {TYPE_1__ target; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* change_handler ) (TYPE_3__*) ;TYPE_2__ value; scalar_t__ offset_by; } ;
typedef  TYPE_3__ rarch_setting_t ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;

/* Variables and functions */
 int action_cancel_pop_default (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int atoi (char const*) ; 
 TYPE_3__* menu_setting_find_enum (int) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static int action_ok_push_dropdown_setting_uint_item(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   unsigned value;
   enum msg_hash_enums enum_idx = (enum msg_hash_enums)atoi(label);
   rarch_setting_t     *setting = menu_setting_find_enum(enum_idx);

   if (!setting)
      return -1;

   value = (unsigned)(idx + setting->offset_by);

#if 0
   if (!string_is_empty(path))
   {
      unsigned path_value = atoi(path);
      if (path_value != value)
         value = path_value;
   }
#endif

   *setting->value.target.unsigned_integer = value;

   if (setting->change_handler)
      setting->change_handler(setting);

   return action_cancel_pop_default(NULL, NULL, 0, 0);
}