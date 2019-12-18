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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  size_word ;
struct TYPE_5__ {void* status; TYPE_1__* module; } ;
typedef  TYPE_2__ VC_CONTAINER_IO_T ;
struct TYPE_4__ {int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 void* VC_CONTAINER_ERROR_FAILED ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 size_t fwrite (void const*,int,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t io_pktfile_write(VC_CONTAINER_IO_T *p_ctx, const void *buffer, size_t size)
{
   uint32_t size_word;
   size_t ret;

   if (size >= 0xFFFFFFFFUL)
      size_word = 0xFFFFFFFFUL;
   else
      size_word = (uint32_t)size;

   ret = fwrite(&size_word, 1, sizeof(size_word), p_ctx->module->stream);
   if (ret != sizeof(size_word))
   {
      p_ctx->status = VC_CONTAINER_ERROR_FAILED;
      return 0;
   }

   ret = fwrite(buffer, 1, size_word, p_ctx->module->stream);
   if (ret != size_word)
      p_ctx->status = VC_CONTAINER_ERROR_FAILED;
   if (fflush(p_ctx->module->stream) != 0)
      p_ctx->status = VC_CONTAINER_ERROR_FAILED;

   return ret;
}