#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* EventHandler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  callbacks_data; int /*<<< orphan*/  omx; TYPE_1__ callbacks; } ;
typedef  scalar_t__ OMX_U32 ;
typedef  int /*<<< orphan*/  OMX_PTR ;
typedef  int /*<<< orphan*/  OMX_HANDLETYPE ;
typedef  scalar_t__ OMX_EVENTTYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_2__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (char*,TYPE_2__*,int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

OMX_ERRORTYPE mmalomx_callback_event_handler(
   MMALOMX_COMPONENT_T *component,
   OMX_EVENTTYPE eEvent,
   OMX_U32 nData1,
   OMX_U32 nData2,
   OMX_PTR pEventData)
{
   LOG_DEBUG("component %p, eEvent %i, nData1 %u, nData2 %u, pEventData %p",
             component, (int)eEvent, (unsigned int)nData1, (unsigned int)nData2, pEventData);
   return component->callbacks.EventHandler((OMX_HANDLETYPE)&component->omx,
         component->callbacks_data, eEvent, nData1, nData2, pEventData);
}