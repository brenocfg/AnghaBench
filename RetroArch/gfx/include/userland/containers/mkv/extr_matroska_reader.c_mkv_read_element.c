#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_9__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_8__ {TYPE_1__* module; } ;
struct TYPE_7__ {int /*<<< orphan*/ * elements_list; } ;
typedef  int /*<<< orphan*/  MKV_ELEMENT_T ;
typedef  int /*<<< orphan*/  MKV_ELEMENT_ID_T ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ mkv_read_element_data (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mkv_read_element_header (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mkv_read_element(VC_CONTAINER_T *p_ctx,
   int64_t size, MKV_ELEMENT_ID_T parent_id)
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   MKV_ELEMENT_T *element = p_ctx->priv->module->elements_list;
   int64_t element_size;
   MKV_ELEMENT_ID_T id;

   status = mkv_read_element_header(p_ctx, size, &id, &element_size, parent_id, &element);
   if(status != VC_CONTAINER_SUCCESS) return status;
   return mkv_read_element_data(p_ctx, element, element_size, size);
}