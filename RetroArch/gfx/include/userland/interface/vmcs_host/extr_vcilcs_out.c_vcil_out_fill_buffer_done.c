#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  (* FillBufferDone ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  callback_state; TYPE_1__ callbacks; } ;
typedef  TYPE_2__ VC_PRIVATE_COMPONENT_T ;
struct TYPE_12__ {int /*<<< orphan*/  ilcs; } ;
struct TYPE_11__ {scalar_t__ pComponentPrivate; } ;
typedef  TYPE_3__ OMX_COMPONENTTYPE ;
typedef  int /*<<< orphan*/  OMX_BUFFERHEADERTYPE ;
typedef  TYPE_4__ ILCS_COMMON_T ;

/* Variables and functions */
 int /*<<< orphan*/ * ilcs_receive_buffer (int /*<<< orphan*/ ,void*,int,TYPE_3__**) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_assert (int /*<<< orphan*/  (*) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 

void vcil_out_fill_buffer_done(ILCS_COMMON_T *st, void *call, int clen, void *resp, int *rlen)
{
   OMX_COMPONENTTYPE *pComp;
   VC_PRIVATE_COMPONENT_T *comp;
   OMX_BUFFERHEADERTYPE *pHeader;

   pHeader = ilcs_receive_buffer(st->ilcs, call, clen, &pComp);
   *rlen = 0;

   if(pHeader)
   {
      comp = (VC_PRIVATE_COMPONENT_T *) pComp->pComponentPrivate;

      vc_assert(comp->callbacks.FillBufferDone);
      comp->callbacks.FillBufferDone(pComp, comp->callback_state, pHeader);
   }
}