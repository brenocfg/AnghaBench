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
struct TYPE_7__ {int /*<<< orphan*/  err; int /*<<< orphan*/  func; } ;
struct TYPE_6__ {int /*<<< orphan*/  param; int /*<<< orphan*/  index; TYPE_1__* reference; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* SetConfig ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ OMX_COMPONENTTYPE ;
typedef  TYPE_2__ IL_SET_EXECUTE_T ;
typedef  TYPE_3__ IL_RESPONSE_HEADER_T ;
typedef  int /*<<< orphan*/  ILCS_COMMON_T ;

/* Variables and functions */
 int /*<<< orphan*/  IL_SET_CONFIG ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vcil_in_set_config(ILCS_COMMON_T *st, void *call, int clen, void *resp, int *rlen)
{
   IL_SET_EXECUTE_T *exe = call;
   IL_RESPONSE_HEADER_T *ret = resp;
   OMX_COMPONENTTYPE *pComp  = exe->reference;

   *rlen = sizeof(IL_RESPONSE_HEADER_T);
   ret->func = IL_SET_CONFIG;
   ret->err = pComp->SetConfig(pComp, exe->index, exe->param);
}