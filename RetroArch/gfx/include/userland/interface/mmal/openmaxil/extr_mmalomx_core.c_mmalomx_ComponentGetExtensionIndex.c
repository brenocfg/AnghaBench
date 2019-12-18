#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  OMX_STRING ;
typedef  int /*<<< orphan*/  OMX_INDEXTYPE ;
typedef  scalar_t__ OMX_HANDLETYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_1__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OMX_ErrorInvalidComponent ; 
 int /*<<< orphan*/  OMX_ErrorInvalidState ; 
 scalar_t__ OMX_StateInvalid ; 
 int /*<<< orphan*/  mmalomx_parameter_extension_index_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static OMX_ERRORTYPE mmalomx_ComponentGetExtensionIndex(
   OMX_HANDLETYPE hComponent,
   OMX_STRING cParameterName,
   OMX_INDEXTYPE* pIndexType)
{
   MMALOMX_COMPONENT_T *component = (MMALOMX_COMPONENT_T *)hComponent;

   LOG_TRACE("hComponent %p, cParameterName %s, pIndexType %p",
             hComponent, cParameterName, pIndexType);

   /* Sanity checks */
   if (!hComponent)
      return OMX_ErrorInvalidComponent;
   if (component->state == OMX_StateInvalid)
      return OMX_ErrorInvalidState;

   return mmalomx_parameter_extension_index_get(cParameterName, pIndexType);
}