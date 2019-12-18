#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; size_t ports_num; TYPE_1__* ports; } ;
struct TYPE_4__ {scalar_t__ enabled; } ;
typedef  size_t OMX_U32 ;
typedef  int /*<<< orphan*/  OMX_TUNNELSETUPTYPE ;
typedef  scalar_t__ OMX_HANDLETYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_2__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,scalar_t__,int,scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (TYPE_2__*) ; 
 int /*<<< orphan*/  OMX_ErrorBadParameter ; 
 int /*<<< orphan*/  OMX_ErrorBadPortIndex ; 
 int /*<<< orphan*/  OMX_ErrorIncorrectStateOperation ; 
 int /*<<< orphan*/  OMX_ErrorInvalidComponent ; 
 int /*<<< orphan*/  OMX_ErrorInvalidState ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
 int /*<<< orphan*/  OMX_ErrorNotImplemented ; 
 scalar_t__ OMX_StateInvalid ; 
 scalar_t__ OMX_StateLoaded ; 

__attribute__((used)) static OMX_ERRORTYPE mmalomx_ComponentTunnelRequest(
   OMX_HANDLETYPE hComponent,
   OMX_U32 nPort,
   OMX_HANDLETYPE hTunneledComp,
   OMX_U32 nTunneledPort,
   OMX_TUNNELSETUPTYPE* pTunnelSetup)
{
   MMALOMX_COMPONENT_T *component = (MMALOMX_COMPONENT_T *)hComponent;
   MMAL_PARAM_UNUSED(component);

   LOG_TRACE("hComponent %p, nPort %i, hTunneledComp %p, nTunneledPort %i, "
             "pTunnelSetup %p", hComponent, (int)nPort, hTunneledComp,
             (int)nTunneledPort, pTunnelSetup);

   /* Sanity checks */
   if (!hComponent)
      return OMX_ErrorInvalidComponent;
   if (component->state == OMX_StateInvalid)
      return OMX_ErrorInvalidState;
   if (nPort >= component->ports_num)
      return OMX_ErrorBadPortIndex;
   if (component->state != OMX_StateLoaded && component->ports[nPort].enabled)
      return OMX_ErrorIncorrectStateOperation;
   if (hTunneledComp && !pTunnelSetup)
      return OMX_ErrorBadParameter;

   if (!hTunneledComp)
      return OMX_ErrorNone;
   return OMX_ErrorNotImplemented;
}