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
struct TYPE_4__ {int triggered; int /*<<< orphan*/  idx; } ;
struct TYPE_5__ {int type; char const* name; char const* short_description; char const* group; char const* parent_group; double min; double max; float step; int enforce_minrange; int enforce_maxrange; int dont_use_enum_idx_representation; TYPE_1__ cmd_trigger; int /*<<< orphan*/ * rounding_fraction; int /*<<< orphan*/  browser_selection_type; scalar_t__ bind_type; int /*<<< orphan*/ * get_string_representation; int /*<<< orphan*/ * action_select; int /*<<< orphan*/ * action_ok; int /*<<< orphan*/ * action_cancel; int /*<<< orphan*/ * action_down; int /*<<< orphan*/ * action_up; int /*<<< orphan*/ * action_right; int /*<<< orphan*/ * action_left; int /*<<< orphan*/ * action_start; int /*<<< orphan*/ * read_handler; int /*<<< orphan*/ * change_handler; scalar_t__ free_flags; scalar_t__ flags; scalar_t__ offset_by; scalar_t__ index_offset; scalar_t__ index; int /*<<< orphan*/ * subgroup; int /*<<< orphan*/ * values; scalar_t__ size; int /*<<< orphan*/  enum_idx; } ;
typedef  TYPE_2__ rarch_setting_t ;
typedef  enum setting_type { ____Placeholder_setting_type } setting_type ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_NONE ; 
 int /*<<< orphan*/  MSG_UNKNOWN ; 
 int /*<<< orphan*/  ST_NONE ; 
 int /*<<< orphan*/  setting_get_string_representation_default ; 

__attribute__((used)) static rarch_setting_t setting_subgroup_setting(enum setting_type type,
      const char* name, const char *parent_name, const char *parent_group,
      bool dont_use_enum_idx)
{
   rarch_setting_t result;

   result.enum_idx                  = MSG_UNKNOWN;
   result.type                      = type;

   result.size                      = 0;

   result.name                      = name;
   result.short_description         = name;
   result.group                     = parent_name;
   result.parent_group              = parent_group;
   result.values                    = NULL;
   result.subgroup                  = NULL;

   result.index                     = 0;
   result.index_offset              = 0;
   result.offset_by                 = 0;

   result.min                       = 0.0;
   result.max                       = 0.0;

   result.flags                     = 0;
   result.free_flags                = 0;

   result.change_handler            = NULL;
   result.read_handler              = NULL;
   result.action_start              = NULL;
   result.action_left               = NULL;
   result.action_right              = NULL;
   result.action_up                 = NULL;
   result.action_down               = NULL;
   result.action_cancel             = NULL;
   result.action_ok                 = NULL;
   result.action_select             = NULL;
   result.get_string_representation = &setting_get_string_representation_default;

   result.bind_type                 = 0;
   result.browser_selection_type    = ST_NONE;
   result.step                      = 0.0f;
   result.rounding_fraction         = NULL;
   result.enforce_minrange          = false;
   result.enforce_maxrange          = false;

   result.cmd_trigger.idx           = CMD_EVENT_NONE;
   result.cmd_trigger.triggered     = false;

   result.dont_use_enum_idx_representation = dont_use_enum_idx;

   return result;
}