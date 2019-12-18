#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int triggered; int /*<<< orphan*/  idx; } ;
struct TYPE_11__ {size_t sizet; } ;
struct TYPE_10__ {size_t sizet; } ;
struct TYPE_8__ {size_t* sizet; } ;
struct TYPE_9__ {TYPE_1__ target; } ;
struct TYPE_13__ {int size; char const* name; char const* short_description; char const* group; char const* subgroup; char const* parent_group; double min; double max; float step; int enforce_minrange; int enforce_maxrange; int dont_use_enum_idx_representation; TYPE_5__ cmd_trigger; TYPE_4__ default_value; TYPE_3__ original_value; TYPE_2__ value; int /*<<< orphan*/ * rounding_fraction; int /*<<< orphan*/  browser_selection_type; scalar_t__ bind_type; int /*<<< orphan*/  get_string_representation; void* action_select; void* action_ok; int /*<<< orphan*/ * action_cancel; int /*<<< orphan*/ * action_down; int /*<<< orphan*/ * action_up; int /*<<< orphan*/  action_right; int /*<<< orphan*/  action_left; int /*<<< orphan*/  action_start; void* read_handler; void* change_handler; scalar_t__ free_flags; scalar_t__ flags; scalar_t__ offset_by; scalar_t__ index_offset; scalar_t__ index; int /*<<< orphan*/ * values; int /*<<< orphan*/  type; int /*<<< orphan*/  enum_idx; } ;
typedef  TYPE_6__ rarch_setting_t ;
typedef  int /*<<< orphan*/  get_string_representation_t ;
typedef  void* change_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_NONE ; 
 int /*<<< orphan*/  MSG_UNKNOWN ; 
 int /*<<< orphan*/  ST_NONE ; 
 int /*<<< orphan*/  ST_SIZE ; 
 void* setting_generic_action_ok_default ; 
 int /*<<< orphan*/  setting_generic_action_start_default ; 
 int /*<<< orphan*/  setting_size_action_left_default ; 
 int /*<<< orphan*/  setting_size_action_right_default ; 

__attribute__((used)) static rarch_setting_t setting_size_setting(const char* name,
      const char* short_description, size_t* target,
      size_t default_value,
      const char *group, const char *subgroup, const char *parent_group,
      change_handler_t change_handler, change_handler_t read_handler,
      bool dont_use_enum_idx, get_string_representation_t string_representation_handler)
{
   rarch_setting_t result;

   result.enum_idx                  = MSG_UNKNOWN;
   result.type                      = ST_SIZE;

   result.size                      = sizeof(size_t);

   result.name                      = name;
   result.short_description         = short_description;
   result.group                     = group;
   result.subgroup                  = subgroup;
   result.parent_group              = parent_group;
   result.values                    = NULL;

   result.index                     = 0;
   result.index_offset              = 0;
   result.offset_by                 = 0;

   result.min                       = 0.0;
   result.max                       = 0.0;

   result.flags                     = 0;
   result.free_flags                = 0;

   result.change_handler            = change_handler;
   result.read_handler              = read_handler;
   result.action_start              = setting_generic_action_start_default;
   result.action_left               = setting_size_action_left_default;
   result.action_right              = setting_size_action_right_default;
   result.action_up                 = NULL;
   result.action_down               = NULL;
   result.action_cancel             = NULL;
   result.action_ok                 = setting_generic_action_ok_default;
   result.action_select             = setting_generic_action_ok_default;
   result.get_string_representation = string_representation_handler;

   result.bind_type                 = 0;
   result.browser_selection_type    = ST_NONE;
   result.step                      = 0.0f;
   result.rounding_fraction         = NULL;
   result.enforce_minrange          = false;
   result.enforce_maxrange          = false;

   result.value.target.sizet   = target;
   result.original_value.sizet = *target;
   result.default_value.sizet  = default_value;

   result.cmd_trigger.idx           = CMD_EVENT_NONE;
   result.cmd_trigger.triggered     = false;

   result.dont_use_enum_idx_representation = dont_use_enum_idx;

   return result;
}