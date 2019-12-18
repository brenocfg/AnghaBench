#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  (* FillBufferDone ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ;int /*<<< orphan*/  (* EmptyBufferDone ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ;} ;
struct TYPE_30__ {int /*<<< orphan*/  callbacks_data; int /*<<< orphan*/  omx; TYPE_1__ callbacks; } ;
struct TYPE_29__ {scalar_t__ direction; int actions; int /*<<< orphan*/  buffers_in_transit; int /*<<< orphan*/  index; TYPE_5__* component; } ;
struct TYPE_28__ {scalar_t__ data; scalar_t__ cmd; scalar_t__ user_data; } ;
struct TYPE_27__ {scalar_t__ pBuffer; int nFlags; } ;
typedef  int /*<<< orphan*/  OMX_HANDLETYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_2__ OMX_BUFFERHEADERTYPE ;
typedef  TYPE_3__ MMAL_BUFFER_HEADER_T ;
typedef  int MMAL_BOOL_T ;
typedef  TYPE_4__ MMALOMX_PORT_T ;
typedef  TYPE_5__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 scalar_t__ ENABLE_MMAL_EXTRA_LOGGING ; 
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int MMALOMX_ACTION_CHECK_FLUSHED ; 
 int /*<<< orphan*/  MMALOMX_LOCK_PORT (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  MMALOMX_UNLOCK_PORT (TYPE_5__*,TYPE_4__*) ; 
 int OMX_BUFFERFLAG_EOS ; 
 scalar_t__ OMX_DirInput ; 
 scalar_t__ OMX_DirOutput ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
 int /*<<< orphan*/  OMX_EventBufferFlag ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_3__*) ; 
 int /*<<< orphan*/  mmalil_buffer_header_to_omx (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  mmalomx_buffer_event (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  mmalomx_callback_event_handler (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmalomx_commands_actions_signal (TYPE_5__*) ; 
 int /*<<< orphan*/  mmalomx_mark_process_outgoing (TYPE_5__*,TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 

OMX_ERRORTYPE mmalomx_buffer_return(
   MMALOMX_PORT_T *port,
   MMAL_BUFFER_HEADER_T *mmal_buffer)
{
   MMALOMX_COMPONENT_T *component = port->component;
   OMX_BUFFERHEADERTYPE *omx_buffer = (OMX_BUFFERHEADERTYPE *)mmal_buffer->user_data;
   MMAL_BOOL_T signal;

   if (mmal_buffer->cmd)
   {
      mmalomx_buffer_event(port, mmal_buffer);
      mmal_buffer_header_release(mmal_buffer);
      return OMX_ErrorNone;
   }

   if (ENABLE_MMAL_EXTRA_LOGGING)
      LOG_TRACE("hComponent %p, port %i, pBuffer %p", component,
                port->index, omx_buffer);

   vcos_assert(omx_buffer->pBuffer == mmal_buffer->data);
   mmalil_buffer_header_to_omx(omx_buffer, mmal_buffer);
   mmal_buffer_header_release(mmal_buffer);

   if ((omx_buffer->nFlags & OMX_BUFFERFLAG_EOS) && port->direction == OMX_DirOutput)
   {
      mmalomx_callback_event_handler(component, OMX_EventBufferFlag,
                                     port->index, omx_buffer->nFlags, NULL);
   }

   mmalomx_mark_process_outgoing(component, port, omx_buffer);

   if (port->direction == OMX_DirInput)
      component->callbacks.EmptyBufferDone((OMX_HANDLETYPE)&component->omx,
         component->callbacks_data, omx_buffer );
   else
      component->callbacks.FillBufferDone((OMX_HANDLETYPE)&component->omx,
         component->callbacks_data, omx_buffer );

   MMALOMX_LOCK_PORT(component, port);
   signal = port->actions & MMALOMX_ACTION_CHECK_FLUSHED;
   port->buffers_in_transit--;
   MMALOMX_UNLOCK_PORT(component, port);

   if (signal)
      mmalomx_commands_actions_signal(component);

   return OMX_ErrorNone;
}