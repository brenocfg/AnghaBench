#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_IO_T ;
struct TYPE_14__ {scalar_t__ offset; size_t size; TYPE_9__* io; scalar_t__ position; scalar_t__ buffer; scalar_t__ buffer_end; } ;
typedef  TYPE_4__ VC_CONTAINER_IO_PRIVATE_CACHE_T ;
struct TYPE_15__ {scalar_t__ (* pf_seek ) (TYPE_9__*,scalar_t__) ;size_t (* pf_read ) (TYPE_9__*,scalar_t__,scalar_t__) ;TYPE_2__* priv; } ;
struct TYPE_12__ {scalar_t__ actual_offset; } ;
struct TYPE_11__ {scalar_t__ actual_offset; } ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ stub1 (TYPE_9__*,scalar_t__) ; 
 size_t stub2 (TYPE_9__*,scalar_t__,scalar_t__) ; 
 size_t vc_container_io_cache_flush (TYPE_3__*,TYPE_4__*,int) ; 

__attribute__((used)) static size_t vc_container_io_cache_refill( VC_CONTAINER_IO_T *p_ctx,
   VC_CONTAINER_IO_PRIVATE_CACHE_T *cache )
{
   size_t ret = vc_container_io_cache_flush( p_ctx, cache, 1 );

   if(ret) return 0; /* TODO what should we do there ? */

   if(p_ctx->priv->actual_offset != cache->offset)
   {
      if(cache->io->pf_seek(cache->io, cache->offset) != VC_CONTAINER_SUCCESS)
         return 0;
   }

   ret = cache->io->pf_read(cache->io, cache->buffer, cache->buffer_end - cache->buffer);
   cache->size = ret;
   cache->position = 0;
   cache->io->priv->actual_offset = cache->offset + ret;
   return ret;
}