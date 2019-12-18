#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  omx; } ;
struct TYPE_13__ {scalar_t__ direction; scalar_t__ marks_num; } ;
struct TYPE_12__ {int /*<<< orphan*/ * pMarkData; int /*<<< orphan*/ * hMarkTargetComponent; } ;
struct TYPE_11__ {int /*<<< orphan*/ * pMarkData; int /*<<< orphan*/ * hMarkTargetComponent; } ;
typedef  TYPE_1__ OMX_MARKTYPE ;
typedef  int /*<<< orphan*/ * OMX_HANDLETYPE ;
typedef  TYPE_2__ OMX_BUFFERHEADERTYPE ;
typedef  TYPE_3__ MMALOMX_PORT_T ;
typedef  TYPE_4__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMALOMX_GET_MARK (TYPE_3__*,TYPE_1__*) ; 
 scalar_t__ OMX_DirOutput ; 
 int /*<<< orphan*/  OMX_EventMark ; 
 int /*<<< orphan*/  mmalomx_callback_event_handler (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mmalomx_mark_process_outgoing(MMALOMX_COMPONENT_T *component,
   MMALOMX_PORT_T *port, OMX_BUFFERHEADERTYPE *omx_buffer)
{
   /* Tag buffers with OMX marks */
   if (port->direction == OMX_DirOutput &&
       !omx_buffer->hMarkTargetComponent && port->marks_num)
   {
         OMX_MARKTYPE *mark;
         MMALOMX_GET_MARK(port, mark);
         omx_buffer->hMarkTargetComponent = mark->hMarkTargetComponent;
         omx_buffer->pMarkData = mark->pMarkData;
   }
   /* Check if we need to trigger a Mark event */
   if (omx_buffer->hMarkTargetComponent &&
       omx_buffer->hMarkTargetComponent == (OMX_HANDLETYPE)&component->omx)
   {
      mmalomx_callback_event_handler(component, OMX_EventMark, 0, 0, omx_buffer->pMarkData);
      omx_buffer->hMarkTargetComponent = NULL;
      omx_buffer->pMarkData = NULL;
   }
}