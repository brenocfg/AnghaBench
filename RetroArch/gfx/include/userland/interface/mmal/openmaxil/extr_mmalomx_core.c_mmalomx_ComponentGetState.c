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
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  OMX_STATETYPE ;
typedef  scalar_t__ OMX_HANDLETYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_1__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (TYPE_1__*) ; 
 int /*<<< orphan*/  OMX_ErrorBadParameter ; 
 int /*<<< orphan*/  OMX_ErrorInvalidComponent ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 

__attribute__((used)) static OMX_ERRORTYPE mmalomx_ComponentGetState(
   OMX_HANDLETYPE hComponent,
   OMX_STATETYPE* pState)
{
   MMALOMX_COMPONENT_T *component = (MMALOMX_COMPONENT_T *)hComponent;
   MMAL_PARAM_UNUSED(component);

   LOG_TRACE("hComponent %p, pState, %p", hComponent, pState);

   /* Sanity checks */
   if (!hComponent)
      return OMX_ErrorInvalidComponent;
   if (!pState)
      return OMX_ErrorBadParameter;

   *pState = component->state;
   return OMX_ErrorNone;
}