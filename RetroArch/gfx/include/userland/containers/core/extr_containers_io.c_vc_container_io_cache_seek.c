#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_15__ {TYPE_1__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_IO_T ;
struct TYPE_16__ {scalar_t__ offset; size_t buffer; size_t mem; TYPE_9__* io; scalar_t__ dirty; scalar_t__ position; scalar_t__ size; } ;
typedef  TYPE_4__ VC_CONTAINER_IO_PRIVATE_CACHE_T ;
struct TYPE_17__ {scalar_t__ (* pf_seek ) (TYPE_9__*,scalar_t__) ;size_t (* pf_read ) (TYPE_9__*,size_t,size_t) ;TYPE_2__* priv; } ;
struct TYPE_14__ {scalar_t__ actual_offset; } ;
struct TYPE_13__ {scalar_t__ async_io; } ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  async_io_wait_complete (scalar_t__,TYPE_4__*,int) ; 
 scalar_t__ stub1 (TYPE_9__*,scalar_t__) ; 
 size_t stub2 (TYPE_9__*,size_t,size_t) ; 
 scalar_t__ stub3 (TYPE_9__*,scalar_t__) ; 
 int /*<<< orphan*/  vc_container_assert (int) ; 
 int /*<<< orphan*/  vc_container_io_cache_flush (TYPE_3__*,TYPE_4__*,int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T vc_container_io_cache_seek(VC_CONTAINER_IO_T *p_ctx,
   VC_CONTAINER_IO_PRIVATE_CACHE_T *cache, int64_t offset)
{
   VC_CONTAINER_STATUS_T status;
   size_t shift, ret;

   /* Check if the seek position is within our cache */
   if(offset >= cache->offset && offset < cache->offset + (int64_t)cache->size)
   {
      cache->position = offset - cache->offset;
      return VC_CONTAINER_SUCCESS;
   }

   shift = cache->buffer - cache->mem;
   if(!cache->dirty && shift && cache->size &&
      offset >= cache->offset - (int64_t)shift && offset < cache->offset)
   {
      /* We need to refill the partial bit of the cache that we didn't take care of last time */
      status = cache->io->pf_seek(cache->io, cache->offset - shift);
      if(status != VC_CONTAINER_SUCCESS) return status;
      cache->offset -= shift;
      cache->buffer -= shift;

      ret = cache->io->pf_read(cache->io, cache->buffer, shift);
      vc_container_assert(ret == shift); /* FIXME: ret must = shift */
      cache->size += shift;
      cache->position = offset - cache->offset;
      cache->io->priv->actual_offset = cache->offset + ret;
      return VC_CONTAINER_SUCCESS;
   }

   if(cache->dirty) vc_container_io_cache_flush( p_ctx, cache, 1 );
   // FIXME: what if all the data couldn't be flushed ?

   if(p_ctx->priv->async_io) async_io_wait_complete( p_ctx->priv->async_io, cache, 1 );

   status = cache->io->pf_seek(cache->io, offset);
   if(status != VC_CONTAINER_SUCCESS) return status;

   vc_container_io_cache_flush( p_ctx, cache, 1 );

   cache->offset = offset;
   cache->io->priv->actual_offset = offset;
   return VC_CONTAINER_SUCCESS;
}