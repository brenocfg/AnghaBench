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
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/  callbacks_data; int /*<<< orphan*/  callbacks; } ;
typedef  int /*<<< orphan*/  OMX_PTR ;
typedef  scalar_t__ OMX_HANDLETYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  int /*<<< orphan*/  OMX_CALLBACKTYPE ;
typedef  TYPE_1__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (TYPE_1__*) ; 
 int /*<<< orphan*/  OMX_ErrorBadParameter ; 
 int /*<<< orphan*/  OMX_ErrorInvalidComponent ; 
 int /*<<< orphan*/  OMX_ErrorInvalidState ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
 scalar_t__ OMX_StateInvalid ; 
 scalar_t__ OMX_StateLoaded ; 

__attribute__((used)) static OMX_ERRORTYPE mmalomx_ComponentSetCallbacks(
   OMX_HANDLETYPE hComponent,
   OMX_CALLBACKTYPE* pCallbacks,
   OMX_PTR pAppData)
{
   MMALOMX_COMPONENT_T *component = (MMALOMX_COMPONENT_T *)hComponent;
   MMAL_PARAM_UNUSED(component);

   LOG_TRACE("hComponent %p, pCallbacks %p, pAppData %p",
              hComponent, pCallbacks, pAppData);

   /* Sanity checks */
   if (!hComponent)
      return OMX_ErrorInvalidComponent;
   if (!pCallbacks)
      return OMX_ErrorBadParameter;
   if (component->state == OMX_StateInvalid)
      return OMX_ErrorInvalidState;

   if (component->state != OMX_StateLoaded)
      return OMX_ErrorInvalidState;

   component->callbacks = *pCallbacks;
   component->callbacks_data = pAppData;
   return OMX_ErrorNone;
}