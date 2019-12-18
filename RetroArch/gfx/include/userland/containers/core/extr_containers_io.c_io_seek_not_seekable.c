#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int64_t ;
typedef  void* VC_CONTAINER_STATUS_T ;
struct TYPE_5__ {unsigned int (* pf_read ) (TYPE_1__*,int /*<<< orphan*/ *,unsigned int) ;void* status; TYPE_2__* priv; } ;
typedef  TYPE_1__ VC_CONTAINER_IO_T ;
struct TYPE_6__ {scalar_t__ actual_offset; } ;
typedef  TYPE_2__ VC_CONTAINER_IO_PRIVATE_T ;

/* Variables and functions */
 unsigned int MIN (scalar_t__,int) ; 
 void* VC_CONTAINER_ERROR_EOS ; 
 void* VC_CONTAINER_SUCCESS ; 
 unsigned int stub1 (TYPE_1__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  vc_container_assert (int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T io_seek_not_seekable(VC_CONTAINER_IO_T *p_ctx, int64_t offset)
{
   VC_CONTAINER_IO_PRIVATE_T *private = p_ctx->priv;

   vc_container_assert(offset >= private->actual_offset);
   if(offset == private->actual_offset)  return VC_CONTAINER_SUCCESS;

   if(offset < private->actual_offset)
   {
      p_ctx->status = VC_CONTAINER_ERROR_EOS;
      return p_ctx->status;
   }

   offset -= private->actual_offset;
   while(offset && !p_ctx->status)
   {
      uint8_t value[64];
      unsigned int ret, size = MIN(offset, 64);
      ret = p_ctx->pf_read(p_ctx, value, size);
      if(ret != size) p_ctx->status = VC_CONTAINER_ERROR_EOS;
      offset -= ret;
   }
   return p_ctx->status;
}