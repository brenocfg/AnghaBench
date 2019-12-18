#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t ports_num; TYPE_1__* ports; } ;
struct TYPE_3__ {size_t marks_num; size_t marks_first; int /*<<< orphan*/ * marks; } ;
typedef  size_t OMX_U32 ;
typedef  int /*<<< orphan*/  OMX_PTR ;
typedef  int /*<<< orphan*/  OMX_MARKTYPE ;
typedef  scalar_t__ OMX_HANDLETYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_1__ MMALOMX_PORT_T ;
typedef  TYPE_2__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 size_t MAX_MARKS_NUM ; 
 int /*<<< orphan*/  OMX_ErrorBadPortIndex ; 
 int /*<<< orphan*/  OMX_ErrorInsufficientResources ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 

OMX_ERRORTYPE mmalomx_command_port_mark(
   OMX_HANDLETYPE hComponent,
   OMX_U32 nPortIndex,
   OMX_PTR *pCmdData)
{
   MMALOMX_COMPONENT_T *component = (MMALOMX_COMPONENT_T *)hComponent;
   OMX_MARKTYPE *mark = (OMX_MARKTYPE *)pCmdData;
   MMALOMX_PORT_T *port;

   if (nPortIndex >= component->ports_num)
      return OMX_ErrorBadPortIndex;
   port = &component->ports[nPortIndex];

   if (port->marks_num == MAX_MARKS_NUM)
      return OMX_ErrorInsufficientResources;

   port->marks[(port->marks_first + port->marks_num) % MAX_MARKS_NUM] = *mark;
   port->marks_num++;

   return OMX_ErrorNone;
}