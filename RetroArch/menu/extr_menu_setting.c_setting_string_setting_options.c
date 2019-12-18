#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* parent_group; char const* values; } ;
typedef  TYPE_1__ rarch_setting_t ;
typedef  enum setting_type { ____Placeholder_setting_type } setting_type ;
typedef  int /*<<< orphan*/  change_handler_t ;

/* Variables and functions */
 TYPE_1__ setting_string_setting (int,char const*,char const*,char*,unsigned int,char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static rarch_setting_t setting_string_setting_options(enum setting_type type,
      const char* name, const char* short_description, char* target,
      unsigned size, const char* default_value,
      const char *empty, const char *values,
      const char *group, const char *subgroup, const char *parent_group,
      change_handler_t change_handler, change_handler_t read_handler,
      bool dont_use_enum_idx)
{
  rarch_setting_t result = setting_string_setting(type, name,
        short_description, target, size, default_value, empty, group,
        subgroup, parent_group, change_handler, read_handler,
        dont_use_enum_idx);

  result.parent_group    = parent_group;
  result.values          = values;
  return result;
}