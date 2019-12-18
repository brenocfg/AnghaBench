#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  actions; } ;
struct TYPE_11__ {int /*<<< orphan*/  request; } ;
struct TYPE_10__ {unsigned int ports_num; size_t state_transition; int /*<<< orphan*/  state; TYPE_4__* ports; } ;
typedef  TYPE_1__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMALOMX_ACTION_NOTIFY_STATE ; 
 int /*<<< orphan*/  MMALOMX_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  MMALOMX_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  OMX_CommandStateSet ; 
 int /*<<< orphan*/  OMX_EventCmdComplete ; 
 int /*<<< orphan*/  mmalomx_callback_event_handler (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmalomx_commands_actions_next (TYPE_1__*) ; 
 int /*<<< orphan*/  mmalomx_commands_check_port_actions (TYPE_1__*,TYPE_4__*) ; 
 TYPE_2__* state_transition_table ; 

void mmalomx_commands_actions_check(MMALOMX_COMPONENT_T *component)
{
   uint32_t actions_left = 0;
   unsigned int i;

   for (i = 0; i < component->ports_num; i++)
      mmalomx_commands_check_port_actions(component, &component->ports[i]);

   MMALOMX_LOCK(component);
   for (i = 0; i < component->ports_num; i++)
      actions_left |= component->ports[i].actions;

   if (!actions_left && component->state_transition)
   {
      component->state = state_transition_table[component->state_transition].request;
      component->state_transition = 0;
      actions_left = MMALOMX_ACTION_NOTIFY_STATE;
   }
   MMALOMX_UNLOCK(component);

   if (actions_left == MMALOMX_ACTION_NOTIFY_STATE)
   {
      mmalomx_callback_event_handler(component, OMX_EventCmdComplete,
         OMX_CommandStateSet, component->state, NULL);
      actions_left = 0;
   }

   /* If we're not currently processing a command, we can start processing
    * the next one. */
   if (!actions_left)
      mmalomx_commands_actions_next(component);
}