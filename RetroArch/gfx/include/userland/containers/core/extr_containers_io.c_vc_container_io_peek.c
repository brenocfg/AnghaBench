#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_9__ {int capabilities; size_t (* pf_read ) (TYPE_2__*,void*,size_t) ;int /*<<< orphan*/  offset; int /*<<< orphan*/  (* pf_seek ) (TYPE_2__*,int /*<<< orphan*/ ) ;TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_IO_T ;
struct TYPE_8__ {scalar_t__ cache; } ;

/* Variables and functions */
 int VC_CONTAINER_IO_CAPS_CANT_SEEK ; 
 size_t stub1 (TYPE_2__*,void*,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 size_t vc_container_io_read (TYPE_2__*,void*,size_t) ; 
 int /*<<< orphan*/  vc_container_io_seek (TYPE_2__*,int /*<<< orphan*/ ) ; 

size_t vc_container_io_peek(VC_CONTAINER_IO_T *p_ctx, void *buffer, size_t size)
{
   size_t ret;

   if(p_ctx->priv->cache)
   {
      /* FIXME: do something a bit more clever than this */
      int64_t offset = p_ctx->offset;
      ret = vc_container_io_read(p_ctx, buffer, size);
      vc_container_io_seek(p_ctx, offset);
      return ret;
   }

   if (p_ctx->capabilities & VC_CONTAINER_IO_CAPS_CANT_SEEK)
      return 0;

   ret = p_ctx->pf_read(p_ctx, buffer, size);
   p_ctx->pf_seek(p_ctx, p_ctx->offset);
   return ret;
}