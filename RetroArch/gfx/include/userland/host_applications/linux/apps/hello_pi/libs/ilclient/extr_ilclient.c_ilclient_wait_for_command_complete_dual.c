#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VCOS_UNSIGNED ;
struct TYPE_9__ {TYPE_1__* event_list; } ;
struct TYPE_8__ {struct TYPE_8__* related; int /*<<< orphan*/  event; TYPE_5__* client; TYPE_1__* list; } ;
struct TYPE_7__ {int eEvent; int nData1; int nData2; struct TYPE_7__* next; } ;
typedef  int OMX_U32 ;
typedef  int OMX_COMMANDTYPE ;
typedef  TYPE_1__ ILEVENT_T ;
typedef  TYPE_2__ COMPONENT_T ;

/* Variables and functions */
 int ILCLIENT_EVENT_ERROR ; 
 int ILCLIENT_PORT_DISABLED ; 
 int ILCLIENT_PORT_ENABLED ; 
 int ILCLIENT_STATE_CHANGED ; 
#define  OMX_CommandPortDisable 130 
#define  OMX_CommandPortEnable 129 
#define  OMX_CommandStateSet 128 
 scalar_t__ OMX_ErrorSameState ; 
 int OMX_EventCmdComplete ; 
 int OMX_EventError ; 
 int /*<<< orphan*/  VCOS_OR_CONSUME ; 
 int /*<<< orphan*/  VCOS_SUSPEND ; 
 int /*<<< orphan*/  ilclient_lock_events (TYPE_5__*) ; 
 int /*<<< orphan*/  ilclient_unlock_events (TYPE_5__*) ; 
 int /*<<< orphan*/  vcos_event_flags_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ilclient_wait_for_command_complete_dual(COMPONENT_T *comp, OMX_COMMANDTYPE command, OMX_U32 nData2, COMPONENT_T *other)
{
   OMX_U32 mask = ILCLIENT_EVENT_ERROR;
   int ret = 0;

   switch(command) {
   case OMX_CommandStateSet:    mask |= ILCLIENT_STATE_CHANGED; break;
   case OMX_CommandPortDisable: mask |= ILCLIENT_PORT_DISABLED; break;
   case OMX_CommandPortEnable:  mask |= ILCLIENT_PORT_ENABLED;  break;
   default: return -1;
   }

   if(other)
      other->related = comp;

   while(1)
   {
      ILEVENT_T *cur, *prev = NULL;
      VCOS_UNSIGNED set;

      ilclient_lock_events(comp->client);

      cur = comp->list;
      while(cur &&
            !(cur->eEvent == OMX_EventCmdComplete && cur->nData1 == command && cur->nData2 == nData2) &&
            !(cur->eEvent == OMX_EventError && cur->nData2 == 1))
      {
         prev = cur;
         cur = cur->next;
      }

      if(cur)
      {
         if(prev == NULL)
            comp->list = cur->next;
         else
            prev->next = cur->next;

         // work out whether this was a success or a fail event
         ret = cur->eEvent == OMX_EventCmdComplete || cur->nData1 == OMX_ErrorSameState ? 0 : -1;

         if(cur->eEvent == OMX_EventError)
            vcos_event_flags_get(&comp->event, ILCLIENT_EVENT_ERROR, VCOS_OR_CONSUME, 0, &set);

         // add back into spare list
         cur->next = comp->client->event_list;
         comp->client->event_list = cur;
         cur->eEvent = -1; // mark as unused

         ilclient_unlock_events(comp->client);
         break;
      }
      else if(other != NULL)
      {
         // check the other component for an error event that terminates a command
         cur = other->list;
         while(cur && !(cur->eEvent == OMX_EventError && cur->nData2 == 1))
            cur = cur->next;

         if(cur)
         {
            // we don't remove the event in this case, since the user
            // can confirm that this event errored by calling wait_for_command on the
            // other component

            ret = -2;
            ilclient_unlock_events(comp->client);
            break;
         }
      }

      ilclient_unlock_events(comp->client);

      vcos_event_flags_get(&comp->event, mask, VCOS_OR_CONSUME, VCOS_SUSPEND, &set);
   }

   if(other)
      other->related = NULL;

   return ret;
}