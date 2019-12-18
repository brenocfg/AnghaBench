#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ state; int /*<<< orphan*/  registry_id; } ;
struct TYPE_7__ {scalar_t__ nVersion; } ;
typedef  TYPE_1__ OMX_VERSIONTYPE ;
typedef  scalar_t__ OMX_UUIDTYPE ;
typedef  char* OMX_STRING ;
typedef  scalar_t__ OMX_HANDLETYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  TYPE_2__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,scalar_t__,char*,TYPE_1__*,TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  OMX_ErrorBadParameter ; 
 int /*<<< orphan*/  OMX_ErrorInvalidComponent ; 
 int /*<<< orphan*/  OMX_ErrorInvalidState ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
 int /*<<< orphan*/  OMX_MAX_STRINGNAME_SIZE ; 
 scalar_t__ OMX_StateInvalid ; 
 scalar_t__ OMX_VERSION ; 
 char* mmalomx_registry_component_name (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 

__attribute__((used)) static OMX_ERRORTYPE mmalomx_ComponentGetComponentVersion(
   OMX_HANDLETYPE hComponent,
   OMX_STRING pComponentName,
   OMX_VERSIONTYPE* pComponentVersion,
   OMX_VERSIONTYPE* pSpecVersion,
   OMX_UUIDTYPE* pComponentUUID)
{
   MMALOMX_COMPONENT_T *component = (MMALOMX_COMPONENT_T *)hComponent;
   const char *short_name, *prefix;

   LOG_TRACE("hComponent %p, componentName %p, componentVersion %p, "
             "pSpecVersion %p, componentUUID %p",
             hComponent, pComponentName, pComponentVersion, pSpecVersion,
             pComponentUUID);

   /* Sanity checks */
   if (!hComponent)
      return OMX_ErrorInvalidComponent;
   if (component->state == OMX_StateInvalid)
      return OMX_ErrorInvalidState;
   if (!pComponentName || !pComponentVersion || !pSpecVersion || !pComponentUUID )
      return OMX_ErrorBadParameter;

   short_name = mmalomx_registry_component_name(component->registry_id, &prefix);

   snprintf(pComponentName, OMX_MAX_STRINGNAME_SIZE, "%s%s", short_name, prefix);
   pComponentVersion->nVersion = 0;
   pSpecVersion->nVersion = OMX_VERSION;
   snprintf((char *)(*pComponentUUID), sizeof(OMX_UUIDTYPE), "%s", pComponentName);

   return OMX_ErrorNone;
}