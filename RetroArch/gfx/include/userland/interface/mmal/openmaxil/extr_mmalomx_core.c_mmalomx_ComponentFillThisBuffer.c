#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ nOutputPortIndex; } ;
typedef  scalar_t__ OMX_HANDLETYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_1__ OMX_BUFFERHEADERTYPE ;
typedef  int /*<<< orphan*/  MMALOMX_COMPONENT_T ;

/* Variables and functions */
 scalar_t__ ENABLE_MMAL_EXTRA_LOGGING ; 
 int /*<<< orphan*/  LOG_TRACE (char*,scalar_t__,int,TYPE_1__*) ; 
 int /*<<< orphan*/  OMX_DirOutput ; 
 int /*<<< orphan*/  mmalomx_buffer_send (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OMX_ERRORTYPE mmalomx_ComponentFillThisBuffer(
   OMX_HANDLETYPE hComponent,
   OMX_BUFFERHEADERTYPE* pBuffer)
{
   MMALOMX_COMPONENT_T *component = (MMALOMX_COMPONENT_T *)hComponent;

   if (ENABLE_MMAL_EXTRA_LOGGING)
      LOG_TRACE("hComponent %p, port %i, pBuffer %p", hComponent,
                pBuffer ? (int)pBuffer->nOutputPortIndex : -1, pBuffer);

  return mmalomx_buffer_send(component, pBuffer, OMX_DirOutput);
}