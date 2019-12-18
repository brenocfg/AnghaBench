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
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_9__ {int /*<<< orphan*/  element_level; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_7__ {TYPE_3__* module; } ;
typedef  int /*<<< orphan*/  MKV_ELEMENT_ID_T ;

/* Variables and functions */
 scalar_t__ MKV_ELEMENT_MIN_HEADER_SIZE ; 
 scalar_t__ STREAM_POSITION (TYPE_2__*) ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ mkv_read_element (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mkv_read_element_ebml(VC_CONTAINER_T *p_ctx,
   MKV_ELEMENT_ID_T id, int64_t size)
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   int64_t offset = STREAM_POSITION(p_ctx);

   /* Read contained elements */
   module->element_level++;
   while(status == VC_CONTAINER_SUCCESS && size >= MKV_ELEMENT_MIN_HEADER_SIZE)
   {
      offset = STREAM_POSITION(p_ctx);
      status = mkv_read_element(p_ctx, size, id);
      size -= (STREAM_POSITION(p_ctx) - offset);
   }
   module->element_level--;
   return status;
}