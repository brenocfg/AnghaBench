#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  gresp ;
typedef  int /*<<< orphan*/  exe ;
typedef  int /*<<< orphan*/  dresp ;
typedef  int /*<<< orphan*/  dexe ;
struct TYPE_20__ {int /*<<< orphan*/  dir; int /*<<< orphan*/  port; } ;
typedef  TYPE_2__ VC_PRIVATE_PORT_T ;
struct TYPE_21__ {int numPorts; struct TYPE_21__* next; TYPE_2__* port; int /*<<< orphan*/  reference; TYPE_5__* comp; } ;
typedef  TYPE_3__ VC_PRIVATE_COMPONENT_T ;
struct TYPE_25__ {int /*<<< orphan*/  param; int /*<<< orphan*/  index; int /*<<< orphan*/  reference; TYPE_5__* mark; int /*<<< orphan*/  name; } ;
struct TYPE_24__ {scalar_t__ err; int numPorts; int portDir; int /*<<< orphan*/ * portIndex; int /*<<< orphan*/  param; int /*<<< orphan*/  reference; } ;
struct TYPE_23__ {int /*<<< orphan*/  ComponentRoleEnum; int /*<<< orphan*/  UseEGLImage; int /*<<< orphan*/  GetExtensionIndex; int /*<<< orphan*/  ComponentTunnelRequest; int /*<<< orphan*/  FillThisBuffer; int /*<<< orphan*/  EmptyThisBuffer; int /*<<< orphan*/  FreeBuffer; int /*<<< orphan*/  AllocateBuffer; int /*<<< orphan*/  UseBuffer; int /*<<< orphan*/  SendCommand; int /*<<< orphan*/  SetConfig; int /*<<< orphan*/  GetConfig; int /*<<< orphan*/  SetParameter; int /*<<< orphan*/  GetParameter; int /*<<< orphan*/  GetState; int /*<<< orphan*/  SetCallbacks; int /*<<< orphan*/  ComponentDeInit; int /*<<< orphan*/  GetComponentVersion; TYPE_12__* pApplicationPrivate; TYPE_3__* pComponentPrivate; } ;
struct TYPE_19__ {int /*<<< orphan*/  nVersion; } ;
struct TYPE_22__ {int nSize; int reqSet; int portDir; int /*<<< orphan*/  portIndex; TYPE_1__ nVersion; } ;
struct TYPE_18__ {int /*<<< orphan*/  component_lock; TYPE_3__* component_list; int /*<<< orphan*/  ilcs; } ;
typedef  int OMX_U32 ;
typedef  int /*<<< orphan*/  OMX_STRING ;
typedef  TYPE_4__ OMX_PARAM_PORTSUMMARYTYPE ;
typedef  scalar_t__ OMX_HANDLETYPE ;
typedef  scalar_t__ OMX_ERRORTYPE ;
typedef  TYPE_5__ OMX_COMPONENTTYPE ;
typedef  TYPE_6__ IL_RESPONSE_HEADER_T ;
typedef  TYPE_6__ IL_GET_RESPONSE_T ;
typedef  TYPE_8__ IL_GET_EXECUTE_T ;
typedef  TYPE_8__ IL_EXECUTE_HEADER_T ;
typedef  TYPE_6__ IL_CREATE_COMPONENT_RESPONSE_T ;
typedef  TYPE_8__ IL_CREATE_COMPONENT_EXECUTE_T ;
typedef  TYPE_12__ ILCS_COMMON_T ;

/* Variables and functions */
 int /*<<< orphan*/  IL_COMPONENT_DEINIT ; 
 int /*<<< orphan*/  IL_CREATE_COMPONENT ; 
 int IL_GET_EXECUTE_HEADER_SIZE ; 
 int /*<<< orphan*/  IL_GET_PARAMETER ; 
 int /*<<< orphan*/  OMX_DirInput ; 
 int /*<<< orphan*/  OMX_DirOutput ; 
 scalar_t__ OMX_ErrorHardware ; 
 scalar_t__ OMX_ErrorInsufficientResources ; 
 scalar_t__ OMX_ErrorInvalidComponent ; 
 scalar_t__ OMX_ErrorNone ; 
 int /*<<< orphan*/  OMX_IndexParamPortSummary ; 
 int /*<<< orphan*/  OMX_VERSION ; 
 scalar_t__ ilcs_execute_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,int,TYPE_6__*,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcil_out_AllocateBuffer ; 
 int /*<<< orphan*/  vcil_out_ComponentDeInit ; 
 int /*<<< orphan*/  vcil_out_ComponentRoleEnum ; 
 int /*<<< orphan*/  vcil_out_ComponentTunnelRequest ; 
 int /*<<< orphan*/  vcil_out_EmptyThisBuffer ; 
 int /*<<< orphan*/  vcil_out_FillThisBuffer ; 
 int /*<<< orphan*/  vcil_out_FreeBuffer ; 
 int /*<<< orphan*/  vcil_out_GetComponentVersion ; 
 int /*<<< orphan*/  vcil_out_GetConfig ; 
 int /*<<< orphan*/  vcil_out_GetExtensionIndex ; 
 int /*<<< orphan*/  vcil_out_GetParameter ; 
 int /*<<< orphan*/  vcil_out_GetState ; 
 int /*<<< orphan*/  vcil_out_SendCommand ; 
 int /*<<< orphan*/  vcil_out_SetCallbacks ; 
 int /*<<< orphan*/  vcil_out_SetConfig ; 
 int /*<<< orphan*/  vcil_out_SetParameter ; 
 int /*<<< orphan*/  vcil_out_UseBuffer ; 
 int /*<<< orphan*/  vcil_out_UseEGLImage ; 
 TYPE_3__* vcos_malloc (int,char*) ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_wait (int /*<<< orphan*/ *) ; 

OMX_ERRORTYPE vcil_out_create_component(ILCS_COMMON_T *st, OMX_HANDLETYPE hComponent, OMX_STRING component_name)
{
   OMX_COMPONENTTYPE *pComp = (OMX_COMPONENTTYPE *) hComponent;
   IL_CREATE_COMPONENT_EXECUTE_T exe;
   IL_CREATE_COMPONENT_RESPONSE_T resp;
   VC_PRIVATE_COMPONENT_T *comp;
   OMX_U32 i;
   int rlen = sizeof(resp);

   if (strlen(component_name) >= sizeof(exe.name))
      return OMX_ErrorInvalidComponent;

   strcpy(exe.name, component_name);
   exe.mark = pComp;

   if(ilcs_execute_function(st->ilcs, IL_CREATE_COMPONENT, &exe, sizeof(exe), &resp, &rlen) < 0 || rlen != sizeof(resp))
      return OMX_ErrorHardware;

   if (resp.err != OMX_ErrorNone)
      return resp.err;

   comp = vcos_malloc(sizeof(VC_PRIVATE_COMPONENT_T) + (sizeof(VC_PRIVATE_PORT_T) * resp.numPorts), "ILCS Host Comp");
   if (!comp)
   {
      IL_EXECUTE_HEADER_T dexe;
      IL_RESPONSE_HEADER_T dresp;
      int dlen = sizeof(dresp);

      dexe.reference = resp.reference;

      ilcs_execute_function(st->ilcs, IL_COMPONENT_DEINIT, &dexe, sizeof(dexe), &dresp, &dlen);
      return OMX_ErrorInsufficientResources;
   }

   memset(comp, 0, sizeof(VC_PRIVATE_COMPONENT_T) + (sizeof(VC_PRIVATE_PORT_T) * resp.numPorts));

   comp->reference = resp.reference;
   comp->comp = pComp;
   comp->numPorts = resp.numPorts;
   comp->port = (VC_PRIVATE_PORT_T *) ((unsigned char *) comp + sizeof(VC_PRIVATE_COMPONENT_T));

   for (i=0; i<comp->numPorts; i++)
   {
      if (i && !(i&0x1f))
      {
         IL_GET_EXECUTE_T gexe;
         IL_GET_RESPONSE_T gresp;
         OMX_PARAM_PORTSUMMARYTYPE *summary;
         int glen = sizeof(gresp);

         gexe.reference = comp->reference;
         gexe.index = OMX_IndexParamPortSummary;

         summary = (OMX_PARAM_PORTSUMMARYTYPE *) &gexe.param;
         summary->nSize = sizeof(OMX_PARAM_PORTSUMMARYTYPE);
         summary->nVersion.nVersion = OMX_VERSION;
         summary->reqSet = i>>5;

         ilcs_execute_function(st->ilcs, IL_GET_PARAMETER, &gexe,
                               sizeof(OMX_PARAM_PORTSUMMARYTYPE)+IL_GET_EXECUTE_HEADER_SIZE,
                               &gresp, &glen);

         summary = (OMX_PARAM_PORTSUMMARYTYPE *) &gresp.param;
         resp.portDir = summary->portDir;
         memcpy(resp.portIndex, summary->portIndex, sizeof(OMX_U32) * 32);
      }

      comp->port[i].port = resp.portIndex[i&0x1f];
      comp->port[i].dir = ((resp.portDir >> (i&0x1f)) & 1) ? OMX_DirOutput : OMX_DirInput;
   }

   vcos_semaphore_wait(&st->component_lock);
   // insert into head of list
   comp->next = st->component_list;
   st->component_list = comp;
   vcos_semaphore_post(&st->component_lock);

   pComp->pComponentPrivate = comp;
   pComp->pApplicationPrivate = st;

   pComp->GetComponentVersion = vcil_out_GetComponentVersion;
   pComp->ComponentDeInit = vcil_out_ComponentDeInit;
   pComp->SetCallbacks = vcil_out_SetCallbacks;
   pComp->GetState = vcil_out_GetState;
   pComp->GetParameter = vcil_out_GetParameter;
   pComp->SetParameter = vcil_out_SetParameter;
   pComp->GetConfig = vcil_out_GetConfig;
   pComp->SetConfig = vcil_out_SetConfig;
   pComp->SendCommand = vcil_out_SendCommand;
   pComp->UseBuffer = vcil_out_UseBuffer;
   pComp->AllocateBuffer = vcil_out_AllocateBuffer;
   pComp->FreeBuffer = vcil_out_FreeBuffer;
   pComp->EmptyThisBuffer = vcil_out_EmptyThisBuffer;
   pComp->FillThisBuffer = vcil_out_FillThisBuffer;
   pComp->ComponentTunnelRequest = vcil_out_ComponentTunnelRequest;
   pComp->GetExtensionIndex = vcil_out_GetExtensionIndex;
   pComp->UseEGLImage = vcil_out_UseEGLImage;
   pComp->ComponentRoleEnum = vcil_out_ComponentRoleEnum;

   return resp.err;
}