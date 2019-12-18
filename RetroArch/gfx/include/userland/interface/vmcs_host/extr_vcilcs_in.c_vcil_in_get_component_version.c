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
struct TYPE_7__ {TYPE_1__* reference; } ;
struct TYPE_6__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/  spec_version; int /*<<< orphan*/  component_version; int /*<<< orphan*/  name; int /*<<< orphan*/  err; int /*<<< orphan*/  func; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* GetComponentVersion ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ OMX_COMPONENTTYPE ;
typedef  TYPE_2__ IL_GET_VERSION_RESPONSE_T ;
typedef  TYPE_3__ IL_EXECUTE_HEADER_T ;
typedef  int /*<<< orphan*/  ILCS_COMMON_T ;

/* Variables and functions */
 int /*<<< orphan*/  IL_GET_COMPONENT_VERSION ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void vcil_in_get_component_version(ILCS_COMMON_T *st, void *call, int clen, void *resp, int *rlen)
{
   IL_EXECUTE_HEADER_T *exe = call;
   IL_GET_VERSION_RESPONSE_T *ret = resp;
   OMX_COMPONENTTYPE *pComp = exe->reference;

   *rlen = sizeof(IL_GET_VERSION_RESPONSE_T);
   ret->func = IL_GET_COMPONENT_VERSION;
   ret->err = pComp->GetComponentVersion(pComp, ret->name, &ret->component_version, &ret->spec_version, &ret->uuid);
}