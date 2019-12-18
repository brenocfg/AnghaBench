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
struct TYPE_11__ {char const* string; } ;
struct TYPE_9__ {char* string; } ;
struct TYPE_10__ {TYPE_2__ target; } ;
struct TYPE_8__ {char const* empty_path; } ;
struct TYPE_13__ {int type; unsigned int size; char const* name; char const* short_description; char const* group; char const* subgroup; char const* parent_group; double min; double max; int browser_selection_type; float step; int enforce_minrange; int enforce_maxrange; int dont_use_enum_idx_representation; int /*<<< orphan*/ * get_string_representation; int /*<<< orphan*/ * action_start; TYPE_5__ cmd_trigger; TYPE_4__ default_value; TYPE_3__ value; TYPE_1__ dir; int /*<<< orphan*/ * rounding_fraction; scalar_t__ bind_type; int /*<<< orphan*/ * action_select; int /*<<< orphan*/ * action_ok; int /*<<< orphan*/ * action_cancel; int /*<<< orphan*/ * action_down; int /*<<< orphan*/ * action_up; int /*<<< orphan*/ * action_right; int /*<<< orphan*/ * action_left; void* read_handler; void* change_handler; scalar_t__ free_flags; scalar_t__ flags; scalar_t__ offset_by; scalar_t__ index_offset; scalar_t__ index; int /*<<< orphan*/ * values; int /*<<< orphan*/  enum_idx; } ;
typedef  TYPE_6__ rarch_setting_t ;
typedef  enum setting_type { ____Placeholder_setting_type } setting_type ;
typedef  void* change_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_NONE ; 
 int /*<<< orphan*/  MSG_UNKNOWN ; 
#define  ST_DIR 129 
 int ST_NONE ; 
#define  ST_PATH 128 
 int /*<<< orphan*/  setting_get_string_representation_st_dir ; 
 int /*<<< orphan*/  setting_get_string_representation_st_path ; 
 int /*<<< orphan*/  setting_get_string_representation_st_string ; 
 void* setting_string_action_start_generic ; 

__attribute__((used)) static rarch_setting_t setting_string_setting(enum setting_type type,
      const char* name, const char* short_description, char* target,
      unsigned size, const char* default_value, const char *empty,
      const char *group, const char *subgroup, const char *parent_group,
      change_handler_t change_handler,
      change_handler_t read_handler,
      bool dont_use_enum_idx)
{
   rarch_setting_t result;

   result.enum_idx                  = MSG_UNKNOWN;
   result.type                      = type;

   result.size                      = size;

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
   result.action_start              = NULL;
   result.action_left               = NULL;
   result.action_right              = NULL;
   result.action_up                 = NULL;
   result.action_down               = NULL;
   result.action_cancel             = NULL;
   result.action_ok                 = NULL;
   result.action_select             = NULL;
   result.get_string_representation = &setting_get_string_representation_st_string;

   result.bind_type                 = 0;
   result.browser_selection_type    = ST_NONE;
   result.step                      = 0.0f;
   result.rounding_fraction         = NULL;
   result.enforce_minrange          = false;
   result.enforce_maxrange          = false;

   result.dir.empty_path            = empty;
   result.value.target.string       = target;
   result.default_value.string      = default_value;

   result.cmd_trigger.idx           = CMD_EVENT_NONE;
   result.cmd_trigger.triggered     = false;

   switch (type)
   {
      case ST_DIR:
         result.action_start              = setting_string_action_start_generic;
         result.browser_selection_type    = ST_DIR;
         result.get_string_representation = &setting_get_string_representation_st_dir;
         break;
      case ST_PATH:
         result.action_start              = setting_string_action_start_generic;
         result.browser_selection_type    = ST_PATH;
         result.get_string_representation = &setting_get_string_representation_st_path;
         break;
      default:
         break;
   }

   result.dont_use_enum_idx_representation = dont_use_enum_idx;

   return result;
}