#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  void* VC_CONTAINER_STATUS_T ;
struct TYPE_3__ {void* status; scalar_t__ module; } ;
typedef  TYPE_1__ VC_CONTAINER_IO_T ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ UINT_MAX ; 
 void* VC_CONTAINER_ERROR_EOS ; 
 void* VC_CONTAINER_ERROR_FAILED ; 
 void* VC_CONTAINER_SUCCESS ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T client_io_seek(VC_CONTAINER_IO_T *p_ctx, int64_t offset)
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   FILE *fd = (FILE *)p_ctx->module;
   int ret;

   //FIXME: no large file support
   if (offset > (int64_t)UINT_MAX)
   {
      LOG_ERROR( 0, "no large file support");
      p_ctx->status = VC_CONTAINER_ERROR_EOS;
      return VC_CONTAINER_ERROR_EOS;
   }

   ret = fseek(fd, (long)offset, SEEK_SET);
   if(ret)
   {
      if( feof(fd) ) status = VC_CONTAINER_ERROR_EOS;
      else status = VC_CONTAINER_ERROR_FAILED;
   }

   p_ctx->status = status;
   return status;
}