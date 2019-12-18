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
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  registry_id; } ;
typedef  int /*<<< orphan*/  OMX_U8 ;
typedef  scalar_t__ OMX_U32 ;
typedef  scalar_t__ OMX_HANDLETYPE ;
typedef  int /*<<< orphan*/  OMX_ERRORTYPE ;
typedef  int /*<<< orphan*/  MMALOMX_ROLE_T ;
typedef  TYPE_1__ MMALOMX_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OMX_ErrorInvalidComponent ; 
 int /*<<< orphan*/  OMX_ErrorInvalidState ; 
 int /*<<< orphan*/  OMX_ErrorNoMore ; 
 int /*<<< orphan*/  OMX_ErrorNone ; 
 scalar_t__ OMX_StateInvalid ; 
 int /*<<< orphan*/  mmalomx_registry_component_roles (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mmalomx_role_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OMX_ERRORTYPE mmalomx_ComponentRoleEnum(
   OMX_HANDLETYPE hComponent,
   OMX_U8 *cRole,
   OMX_U32 nIndex)
{
   MMALOMX_COMPONENT_T *component = (MMALOMX_COMPONENT_T *)hComponent;
   MMALOMX_ROLE_T role;

   LOG_TRACE("hComponent %p, cRole %p, nIndex %i",
             hComponent, cRole, (int)nIndex);

   /* Sanity checks */
   if (!hComponent)
      return OMX_ErrorInvalidComponent;
   if (component->state == OMX_StateInvalid)
      return OMX_ErrorInvalidState;

   role = mmalomx_registry_component_roles(component->registry_id, nIndex);
   if (!role)
      return OMX_ErrorNoMore;
   if (!mmalomx_role_to_name(role))
      return OMX_ErrorNoMore;

   strcpy((char *)cRole, mmalomx_role_to_name(role));
   return OMX_ErrorNone;
}