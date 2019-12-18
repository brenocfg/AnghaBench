#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * pOutputPortPrivate; int /*<<< orphan*/ * pInputPortPrivate; } ;
struct TYPE_14__ {int /*<<< orphan*/  port; int /*<<< orphan*/  size; int /*<<< orphan*/  bufferReference; TYPE_3__* reference; } ;
struct TYPE_13__ {scalar_t__ err; TYPE_9__ bufferHeader; int /*<<< orphan*/ * reference; int /*<<< orphan*/  func; } ;
struct TYPE_12__ {scalar_t__ (* UseBuffer ) (TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ (* GetParameter ) (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  nVersion; } ;
struct TYPE_11__ {int nSize; scalar_t__ eDir; int /*<<< orphan*/  nPortIndex; TYPE_1__ nVersion; } ;
typedef  int /*<<< orphan*/  OMX_U8 ;
typedef  TYPE_2__ OMX_PARAM_PORTDEFINITIONTYPE ;
typedef  scalar_t__ OMX_ERRORTYPE ;
typedef  TYPE_3__ OMX_COMPONENTTYPE ;
typedef  int /*<<< orphan*/  OMX_BUFFERHEADERTYPE ;
typedef  TYPE_4__ IL_ADD_BUFFER_RESPONSE_T ;
typedef  TYPE_5__ IL_ADD_BUFFER_EXECUTE_T ;
typedef  int /*<<< orphan*/  ILCS_COMMON_T ;

/* Variables and functions */
 int /*<<< orphan*/  IL_USE_BUFFER ; 
 scalar_t__ OMX_DirInput ; 
 scalar_t__ OMX_ErrorInsufficientResources ; 
 scalar_t__ OMX_ErrorNone ; 
 int /*<<< orphan*/  OMX_IndexParamPortDefinition ; 
 int /*<<< orphan*/  OMX_VERSION ; 
 int /*<<< orphan*/  memcpy (TYPE_9__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vc_assert (int) ; 
 int /*<<< orphan*/  vcos_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vcos_malloc_aligned (int /*<<< orphan*/ ,int,char*) ; 

void vcil_in_use_buffer(ILCS_COMMON_T *st, void *call, int clen, void *resp, int *rlen)
{
   IL_ADD_BUFFER_EXECUTE_T *exe = call;
   IL_ADD_BUFFER_RESPONSE_T *ret = resp;
   OMX_COMPONENTTYPE *pComp = exe->reference;
   OMX_U8 *buffer;
   OMX_BUFFERHEADERTYPE *bufferHeader;

   *rlen = sizeof(IL_ADD_BUFFER_RESPONSE_T);

   buffer = vcos_malloc_aligned(exe->size, 32, "vcin mapping buffer"); // 32-byte aligned
   if (!buffer)
   {
      ret->err = OMX_ErrorInsufficientResources;
      return;
   }

   //OMX_OSAL_Trace(OMX_OSAL_TRACE_COMPONENT, "hostcomp: use buffer(%p)\n", buffer);
   ret->func = IL_USE_BUFFER;
   ret->err = pComp->UseBuffer(pComp, &bufferHeader, exe->port, exe->bufferReference, exe->size, buffer);

   if (ret->err == OMX_ErrorNone)
   {
      // we're going to pass this buffer to VC
      // initialise our private field in their copy with the host buffer reference
      OMX_PARAM_PORTDEFINITIONTYPE def;
      OMX_ERRORTYPE error;
      def.nSize = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
      def.nVersion.nVersion = OMX_VERSION;
      def.nPortIndex = exe->port;
      error = pComp->GetParameter(pComp, OMX_IndexParamPortDefinition, &def);
      vc_assert(error == OMX_ErrorNone);

      ret->reference = bufferHeader;
      memcpy(&ret->bufferHeader, bufferHeader, sizeof(OMX_BUFFERHEADERTYPE));

      if (def.eDir == OMX_DirInput)
         ret->bufferHeader.pInputPortPrivate = bufferHeader;
      else
         ret->bufferHeader.pOutputPortPrivate = bufferHeader;
   }
   else
      vcos_free(buffer);
}