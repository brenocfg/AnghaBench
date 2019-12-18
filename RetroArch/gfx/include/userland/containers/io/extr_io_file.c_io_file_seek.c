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
typedef  scalar_t__ int64_t ;
typedef  void* VC_CONTAINER_STATUS_T ;
struct TYPE_5__ {void* status; TYPE_1__* module; } ;
typedef  TYPE_2__ VC_CONTAINER_IO_T ;
struct TYPE_4__ {int /*<<< orphan*/ * stream; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int SEEK_SET ; 
 scalar_t__ UINT_MAX ; 
 void* VC_CONTAINER_ERROR_EOS ; 
 void* VC_CONTAINER_ERROR_FAILED ; 
 void* VC_CONTAINER_SUCCESS ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int fseek (int /*<<< orphan*/ *,long,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T io_file_seek(VC_CONTAINER_IO_T *p_ctx, int64_t offset)
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   int ret;

   //FIXME: large file support
#ifdef _VIDEOCORE
   extern int fseek64(FILE *fp, int64_t offset, int whence);
   ret = fseek64(p_ctx->module->stream, offset, SEEK_SET);
#else
   if (offset > (int64_t)UINT_MAX)
   {
      p_ctx->status = VC_CONTAINER_ERROR_EOS;
      return VC_CONTAINER_ERROR_EOS;
   }
   ret = fseek(p_ctx->module->stream, (long)offset, SEEK_SET);
#endif
   if(ret)
   {
      if( feof(p_ctx->module->stream) ) status = VC_CONTAINER_ERROR_EOS;
      else status = VC_CONTAINER_ERROR_FAILED;
   }

   p_ctx->status = status;
   return status;
}