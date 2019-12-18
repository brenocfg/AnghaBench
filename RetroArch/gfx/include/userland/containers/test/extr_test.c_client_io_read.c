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
struct TYPE_3__ {int /*<<< orphan*/  status; scalar_t__ module; } ;
typedef  TYPE_1__ VC_CONTAINER_IO_T ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_EOS ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FAILED ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 size_t fread (void*,int,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t client_io_read(VC_CONTAINER_IO_T *p_ctx, void *buffer, size_t size)
{
   FILE *fd = (FILE *)p_ctx->module;
   size_t ret = fread(buffer, 1, size, fd);
   if(ret != size)
   {
      /* Sanity check return value. Some platforms (e.g. Android) can return -1 */
      if( ((int)ret) < 0 ) ret = 0;

      if( feof(fd) ) p_ctx->status = VC_CONTAINER_ERROR_EOS;
      else p_ctx->status = VC_CONTAINER_ERROR_FAILED;
   }
   LOG_DEBUG( 0, "read: %i", ret );
   return ret;
}