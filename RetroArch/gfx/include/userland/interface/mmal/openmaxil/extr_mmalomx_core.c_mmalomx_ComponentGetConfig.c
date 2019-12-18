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
typedef  int /*<<< orphan*/  OMX_VERSIONTYPE ;
typedef  int OMX_U32 ;
typedef  scalar_t__ OMX_PTR ;
typedef  int /*<<< orphan*/  OMX_INDEXTYPE ;
typedef  scalar_t__ OMX_HANDLETYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_1__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  OMX_ErrorBadParameter ; 
 int /*<<< orphan*/  OMX_ErrorInvalidComponent ; 
 int /*<<< orphan*/  OMX_ErrorInvalidState ; 
 scalar_t__ OMX_StateInvalid ; 
 int /*<<< orphan*/  mmalomx_param_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmalomx_parameter_get (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static OMX_ERRORTYPE mmalomx_ComponentGetConfig(
   OMX_HANDLETYPE hComponent,
   OMX_INDEXTYPE nParamIndex,
   OMX_PTR pParam)
{
   MMALOMX_COMPONENT_T *component = (MMALOMX_COMPONENT_T *)hComponent;

   LOG_TRACE("hComponent %p, nParamIndex 0x%x (%s), pParam %p",
             hComponent, nParamIndex, mmalomx_param_to_string(nParamIndex), pParam);

   /* Sanity checks */
   if (!hComponent)
      return OMX_ErrorInvalidComponent;
   if (!pParam)
      return OMX_ErrorBadParameter;
   if (*(OMX_U32 *)pParam < sizeof(OMX_U32) + sizeof(OMX_VERSIONTYPE))
      return OMX_ErrorBadParameter;
   if (component->state == OMX_StateInvalid)
      return OMX_ErrorInvalidState;

   return mmalomx_parameter_get(component, nParamIndex, pParam);
}