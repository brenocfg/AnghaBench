#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ direction; scalar_t__ marks_num; } ;
struct TYPE_16__ {unsigned int ports_num; TYPE_9__* ports; } ;
struct TYPE_15__ {scalar_t__ marks_num; scalar_t__ direction; int /*<<< orphan*/  index; } ;
struct TYPE_14__ {int /*<<< orphan*/  pMarkData; scalar_t__ hMarkTargetComponent; } ;
struct TYPE_13__ {int /*<<< orphan*/  member_1; scalar_t__ member_0; int /*<<< orphan*/  pMarkData; scalar_t__ hMarkTargetComponent; } ;
typedef  TYPE_1__ OMX_MARKTYPE ;
typedef  TYPE_2__ OMX_BUFFERHEADERTYPE ;
typedef  TYPE_3__ MMALOMX_PORT_T ;
typedef  TYPE_4__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 scalar_t__ MAX_MARKS_NUM ; 
 int /*<<< orphan*/  MMALOMX_GET_MARK (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  MMALOMX_PUT_MARK (TYPE_9__*,TYPE_1__*) ; 
 int /*<<< orphan*/  OMX_CommandMarkBuffer ; 
 scalar_t__ OMX_DirInput ; 
 scalar_t__ OMX_DirOutput ; 
 int /*<<< orphan*/  OMX_EventCmdComplete ; 
 int /*<<< orphan*/  mmalomx_callback_event_handler (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mmalomx_mark_process_incoming(MMALOMX_COMPONENT_T *component,
   MMALOMX_PORT_T *port, OMX_BUFFERHEADERTYPE *omx_buffer)
{
   /* Tag buffers with OMX marks */
   if (!omx_buffer->hMarkTargetComponent && port->marks_num > 0 &&
       port->direction == OMX_DirInput)
   {
      OMX_MARKTYPE *mark;
      MMALOMX_GET_MARK(port, mark);
      omx_buffer->hMarkTargetComponent = mark->hMarkTargetComponent;
      omx_buffer->pMarkData = mark->pMarkData;

      mmalomx_callback_event_handler(component, OMX_EventCmdComplete,
         OMX_CommandMarkBuffer, port->index, NULL);
   }
   /* We do not support buffer marks properly other than for conformance testing.
    * For input ports, we just move the mark over to the output port. */
   if (port->direction == OMX_DirInput && omx_buffer->hMarkTargetComponent)
   {
      OMX_MARKTYPE mark = {omx_buffer->hMarkTargetComponent, omx_buffer->pMarkData};
      unsigned int i;
      for (i = 0; i < component->ports_num; i++)
      {
         if (component->ports[i].direction != OMX_DirOutput ||
             component->ports[i].marks_num >= MAX_MARKS_NUM)
            continue;

         MMALOMX_PUT_MARK((&component->ports[i]), (&mark));
      }
   }
}