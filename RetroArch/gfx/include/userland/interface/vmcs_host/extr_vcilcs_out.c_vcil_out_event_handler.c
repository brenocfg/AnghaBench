#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* EventHandler ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  callback_state; TYPE_1__ callbacks; } ;
typedef  TYPE_2__ VC_PRIVATE_COMPONENT_T ;
struct TYPE_10__ {int /*<<< orphan*/  eventdata; int /*<<< orphan*/  data2; int /*<<< orphan*/  data1; int /*<<< orphan*/  event; TYPE_3__* reference; } ;
struct TYPE_9__ {scalar_t__ pComponentPrivate; } ;
typedef  TYPE_3__ OMX_COMPONENTTYPE ;
typedef  TYPE_4__ IL_EVENT_HANDLER_EXECUTE_T ;
typedef  int /*<<< orphan*/  ILCS_COMMON_T ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/  (*) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 

void vcil_out_event_handler(ILCS_COMMON_T *st, void *call, int clen, void *resp, int *rlen)
{
   IL_EVENT_HANDLER_EXECUTE_T *exe = call;
   OMX_COMPONENTTYPE *pComp = exe->reference;
   VC_PRIVATE_COMPONENT_T *comp = (VC_PRIVATE_COMPONENT_T *) pComp->pComponentPrivate;

   *rlen = 0;

   vcos_assert(comp->callbacks.EventHandler);
   comp->callbacks.EventHandler(pComp, comp->callback_state, exe->event, exe->data1, exe->data2, exe->eventdata);
}