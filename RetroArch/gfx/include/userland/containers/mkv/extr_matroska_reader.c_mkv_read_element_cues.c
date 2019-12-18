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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_7__ {int /*<<< orphan*/  element_offset; int /*<<< orphan*/  cues_offset; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_5__ {TYPE_3__* module; } ;
typedef  int /*<<< orphan*/  MKV_ELEMENT_ID_T ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mkv_read_element_cues( VC_CONTAINER_T *p_ctx, MKV_ELEMENT_ID_T id, int64_t size )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_PARAM_UNUSED(id);
   VC_CONTAINER_PARAM_UNUSED(size);
   module->cues_offset = module->element_offset;
   return VC_CONTAINER_SUCCESS;
}