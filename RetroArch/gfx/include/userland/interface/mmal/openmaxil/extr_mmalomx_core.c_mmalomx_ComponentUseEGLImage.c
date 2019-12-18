#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ state; } ;
typedef  scalar_t__ OMX_U32 ;
typedef  int /*<<< orphan*/  OMX_PTR ;
typedef  scalar_t__ OMX_HANDLETYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  int /*<<< orphan*/  OMX_BUFFERHEADERTYPE ;
typedef  TYPE_1__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,scalar_t__,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (TYPE_1__*) ; 
 int /*<<< orphan*/  OMX_ErrorInvalidComponent ; 
 int /*<<< orphan*/  OMX_ErrorInvalidState ; 
 int /*<<< orphan*/  OMX_ErrorNotImplemented ; 
 scalar_t__ OMX_StateInvalid ; 

__attribute__((used)) static OMX_ERRORTYPE mmalomx_ComponentUseEGLImage(
   OMX_HANDLETYPE hComponent,
   OMX_BUFFERHEADERTYPE** ppBufferHdr,
   OMX_U32 nPortIndex,
   OMX_PTR pAppPrivate,
   void* eglImage)
{
   MMALOMX_COMPONENT_T *component = (MMALOMX_COMPONENT_T *)hComponent;
   MMAL_PARAM_UNUSED(component);

   LOG_TRACE("hComponent %p, ppBufferHdr %p, nPortIndex %i, pAppPrivate %p,"
             " eglImage %p", hComponent, ppBufferHdr, (int)nPortIndex,
             pAppPrivate, eglImage);

   /* Sanity checks */
   if (!hComponent)
      return OMX_ErrorInvalidComponent;
   if (component->state == OMX_StateInvalid)
      return OMX_ErrorInvalidState;

   return OMX_ErrorNotImplemented;
}