#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  param; int /*<<< orphan*/  index; TYPE_1__* reference; } ;
struct TYPE_6__ {int /*<<< orphan*/  param; int /*<<< orphan*/  err; int /*<<< orphan*/  func; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* GetParameter ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int OMX_U32 ;
typedef  TYPE_1__ OMX_COMPONENTTYPE ;
typedef  TYPE_2__ IL_GET_RESPONSE_T ;
typedef  TYPE_3__ IL_GET_EXECUTE_T ;
typedef  int /*<<< orphan*/  ILCS_COMMON_T ;

/* Variables and functions */
 int /*<<< orphan*/  IL_GET_PARAMETER ; 
 int IL_GET_RESPONSE_HEADER_SIZE ; 
 int /*<<< orphan*/  OMX_ErrorHardware ; 
 int VC_ILCS_MAX_PARAM_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vcil_in_get_parameter(ILCS_COMMON_T *st, void *call, int clen, void *resp, int *rlen)
{
   IL_GET_EXECUTE_T *exe = call;
   IL_GET_RESPONSE_T *ret = resp;
   OMX_COMPONENTTYPE *pComp  = exe->reference;
   OMX_U32 size = *((OMX_U32 *) (&exe->param));

   ret->func = IL_GET_PARAMETER;

   if(size > VC_ILCS_MAX_PARAM_SIZE)
   {
      *rlen = IL_GET_RESPONSE_HEADER_SIZE;
      ret->err = OMX_ErrorHardware;
   }
   else
   {
      *rlen = size + IL_GET_RESPONSE_HEADER_SIZE;
      ret->err = pComp->GetParameter(pComp, exe->index, exe->param);
      memcpy(ret->param, exe->param, size);
   }
}