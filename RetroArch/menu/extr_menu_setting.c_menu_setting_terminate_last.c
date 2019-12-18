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
struct TYPE_5__ {double min; double max; float step; int enforce_minrange; int enforce_maxrange; int dont_use_enum_idx_representation; TYPE_1__ cmd_trigger; int /*<<< orphan*/ * rounding_fraction; void* browser_selection_type; scalar_t__ bind_type; int /*<<< orphan*/ * get_string_representation; int /*<<< orphan*/ * action_select; int /*<<< orphan*/ * action_ok; int /*<<< orphan*/ * action_cancel; int /*<<< orphan*/ * action_down; int /*<<< orphan*/ * action_up; int /*<<< orphan*/ * action_right; int /*<<< orphan*/ * action_left; int /*<<< orphan*/ * action_start; int /*<<< orphan*/ * read_handler; int /*<<< orphan*/ * change_handler; scalar_t__ free_flags; scalar_t__ flags; scalar_t__ index_offset; scalar_t__ index; int /*<<< orphan*/ * values; int /*<<< orphan*/ * parent_group; int /*<<< orphan*/ * subgroup; int /*<<< orphan*/ * group; int /*<<< orphan*/ * short_description; int /*<<< orphan*/ * name; scalar_t__ size; void* type; int /*<<< orphan*/  enum_idx; } ;
typedef  TYPE_2__ rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EVENT_NONE ; 
 int /*<<< orphan*/  MSG_UNKNOWN ; 
 void* ST_NONE ; 

__attribute__((used)) static void menu_setting_terminate_last(rarch_setting_t *list, unsigned pos)
{
   (*&list)[pos].enum_idx           = MSG_UNKNOWN;
   (*&list)[pos].type               = ST_NONE;
   (*&list)[pos].size               = 0;
   (*&list)[pos].name               = NULL;
   (*&list)[pos].short_description  = NULL;
   (*&list)[pos].group              = NULL;
   (*&list)[pos].subgroup           = NULL;
   (*&list)[pos].parent_group       = NULL;
   (*&list)[pos].values             = NULL;
   (*&list)[pos].index              = 0;
   (*&list)[pos].index_offset       = 0;
   (*&list)[pos].min                = 0.0;
   (*&list)[pos].max                = 0.0;
   (*&list)[pos].flags              = 0;
   (*&list)[pos].free_flags         = 0;
   (*&list)[pos].change_handler     = NULL;
   (*&list)[pos].read_handler       = NULL;
   (*&list)[pos].action_start       = NULL;
   (*&list)[pos].action_left        = NULL;
   (*&list)[pos].action_right       = NULL;
   (*&list)[pos].action_up          = NULL;
   (*&list)[pos].action_down        = NULL;
   (*&list)[pos].action_cancel      = NULL;
   (*&list)[pos].action_ok          = NULL;
   (*&list)[pos].action_select      = NULL;
   (*&list)[pos].get_string_representation = NULL;
   (*&list)[pos].bind_type          = 0;
   (*&list)[pos].browser_selection_type = ST_NONE;
   (*&list)[pos].step               = 0.0f;
   (*&list)[pos].rounding_fraction  = NULL;
   (*&list)[pos].enforce_minrange   = false;
   (*&list)[pos].enforce_maxrange   = false;
   (*&list)[pos].cmd_trigger.idx    = CMD_EVENT_NONE;
   (*&list)[pos].cmd_trigger.triggered = false;
   (*&list)[pos].dont_use_enum_idx_representation = false;
}