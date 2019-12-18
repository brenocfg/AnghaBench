#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct retro_keybind {int dummy; } ;
struct TYPE_10__ {int triggered; int /*<<< orphan*/  idx; } ;
struct TYPE_9__ {struct retro_keybind const* keybind; } ;
struct TYPE_7__ {struct retro_keybind* keybind; } ;
struct TYPE_8__ {TYPE_1__ target; } ;
struct TYPE_11__ {char const* name; char const* short_description; char const* group; char const* subgroup; char const* parent_group; double min; double max; float step; int enforce_minrange; int enforce_maxrange; int dont_use_enum_idx_representation; TYPE_4__ cmd_trigger; TYPE_3__ default_value; TYPE_2__ value; int /*<<< orphan*/ * rounding_fraction; int /*<<< orphan*/  browser_selection_type; scalar_t__ bind_type; int /*<<< orphan*/ * get_string_representation; void* action_select; void* action_ok; int /*<<< orphan*/ * action_cancel; int /*<<< orphan*/ * action_down; int /*<<< orphan*/ * action_up; int /*<<< orphan*/ * action_right; int /*<<< orphan*/ * action_left; int /*<<< orphan*/  action_start; int /*<<< orphan*/ * read_handler; int /*<<< orphan*/ * change_handler; scalar_t__ free_flags; scalar_t__ flags; scalar_t__ offset_by; void* index_offset; void* index; int /*<<< orphan*/ * values; scalar_t__ size; int /*<<< orphan*/  type; int /*<<< orphan*/  enum_idx; } ;
typedef  TYPE_5__ rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_NONE ; 
 int /*<<< orphan*/  MSG_UNKNOWN ; 
 int /*<<< orphan*/  ST_BIND ; 
 int /*<<< orphan*/  ST_NONE ; 
 void* setting_bind_action_ok ; 
 int /*<<< orphan*/  setting_bind_action_start ; 
 int /*<<< orphan*/  setting_get_string_representation_st_bind ; 

__attribute__((used)) static rarch_setting_t setting_bind_setting(const char* name,
      const char* short_description, struct retro_keybind* target,
      uint32_t idx, uint32_t idx_offset,
      const struct retro_keybind* default_value,
      const char *group, const char *subgroup,
      const char *parent_group,
      bool dont_use_enum_idx)
{
   rarch_setting_t result;

   result.enum_idx                  = MSG_UNKNOWN;
   result.type                      = ST_BIND;

   result.size                      = 0;

   result.name                      = name;
   result.short_description         = short_description;
   result.group                     = group;
   result.subgroup                  = subgroup;
   result.parent_group              = parent_group;
   result.values                    = NULL;

   result.index                     = idx;
   result.index_offset              = idx_offset;
   result.offset_by                 = 0;

   result.min                       = 0.0;
   result.max                       = 0.0;

   result.flags                     = 0;
   result.free_flags                = 0;

   result.change_handler            = NULL;
   result.read_handler              = NULL;
   result.action_start              = setting_bind_action_start;
   result.action_left               = NULL;
   result.action_right              = NULL;
   result.action_up                 = NULL;
   result.action_down               = NULL;
   result.action_cancel             = NULL;
   result.action_ok                 = setting_bind_action_ok;
   result.action_select             = setting_bind_action_ok;
   result.get_string_representation = &setting_get_string_representation_st_bind;

   result.bind_type                 = 0;
   result.browser_selection_type    = ST_NONE;
   result.step                      = 0.0f;
   result.rounding_fraction         = NULL;
   result.enforce_minrange          = false;
   result.enforce_maxrange          = false;

   result.value.target.keybind      = target;
   result.default_value.keybind     = default_value;

   result.cmd_trigger.idx           = CMD_EVENT_NONE;
   result.cmd_trigger.triggered     = false;

   result.dont_use_enum_idx_representation = dont_use_enum_idx;

   return result;
}