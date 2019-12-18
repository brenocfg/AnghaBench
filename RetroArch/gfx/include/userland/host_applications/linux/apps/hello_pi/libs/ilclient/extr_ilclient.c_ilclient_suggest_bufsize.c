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
typedef  int /*<<< orphan*/  param ;
struct TYPE_4__ {int /*<<< orphan*/  nVersion; } ;
struct TYPE_5__ {int nSize; int /*<<< orphan*/  nBufferSize; TYPE_1__ nVersion; } ;
typedef  int /*<<< orphan*/  OMX_U32 ;
typedef  TYPE_2__ OMX_PARAM_BRCMOUTPUTBUFFERSIZETYPE ;
typedef  scalar_t__ OMX_ERRORTYPE ;
typedef  int /*<<< orphan*/  COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  ILC_GET_HANDLE (int /*<<< orphan*/ *) ; 
 scalar_t__ OMX_ErrorNone ; 
 int /*<<< orphan*/  OMX_IndexParamBrcmOutputBufferSize ; 
 scalar_t__ OMX_SetParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  OMX_VERSION ; 
 int /*<<< orphan*/  assert (int) ; 

int ilclient_suggest_bufsize(COMPONENT_T *comp, OMX_U32 nBufSizeHint)
{
   OMX_PARAM_BRCMOUTPUTBUFFERSIZETYPE param;
   OMX_ERRORTYPE error;

   param.nSize = sizeof(param);
   param.nVersion.nVersion = OMX_VERSION;
   param.nBufferSize = nBufSizeHint;
   error = OMX_SetParameter(ILC_GET_HANDLE(comp), OMX_IndexParamBrcmOutputBufferSize,
                            &param);
   assert(error == OMX_ErrorNone);

   return (error == OMX_ErrorNone) ? 0 : -1;
}