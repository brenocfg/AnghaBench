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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  length ;
struct TYPE_4__ {void* status; TYPE_2__* module; } ;
typedef  TYPE_1__ VC_CONTAINER_IO_T ;
struct TYPE_5__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  is_native_order; } ;
typedef  TYPE_2__ VC_CONTAINER_IO_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 void* VC_CONTAINER_ERROR_EOS ; 
 void* VC_CONTAINER_ERROR_FAILED ; 
 scalar_t__ feof (int /*<<< orphan*/ ) ; 
 size_t fread (void*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int swap_byte_order (int) ; 
 int /*<<< orphan*/  vc_container_assert (int) ; 

__attribute__((used)) static size_t io_pktfile_read(VC_CONTAINER_IO_T *p_ctx, void *buffer, size_t size)
{
   VC_CONTAINER_IO_MODULE_T *module = p_ctx->module;
   uint32_t length = 0;
   size_t ret;

   ret = fread(&length, 1, sizeof(length), module->stream);
   if (ret != sizeof(length))
   {
      if( feof(module->stream) ) p_ctx->status = VC_CONTAINER_ERROR_EOS;
      else p_ctx->status = VC_CONTAINER_ERROR_FAILED;
      return 0;
   }

   if (!module->is_native_order)
      length = swap_byte_order(length);

   if (length > 1<<20)
   {
      p_ctx->status = VC_CONTAINER_ERROR_FAILED;
      return 0;
   }

   if (size > length)
      size = length;
   ret = fread(buffer, 1, size, module->stream);
   if(ret != size)
   {
      if( feof(module->stream) ) p_ctx->status = VC_CONTAINER_ERROR_EOS;
      else p_ctx->status = VC_CONTAINER_ERROR_FAILED;
   }
   else if (length > size)
   {
      /* Not enough space to read all the packet, so skip to the next one. */
      length -= size;
      vc_container_assert((long)length > 0);
      fseek(module->stream, (long)length, SEEK_CUR);
   }

   return ret;
}