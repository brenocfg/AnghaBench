#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
typedef  int int32_t ;
struct TYPE_12__ {int offset; TYPE_1__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_IO_T ;
struct TYPE_13__ {scalar_t__ size; int dirty; size_t buffer_end; size_t buffer; size_t position; size_t mem_size; int offset; TYPE_9__* io; } ;
typedef  TYPE_4__ VC_CONTAINER_IO_PRIVATE_CACHE_T ;
struct TYPE_14__ {size_t (* pf_write ) (TYPE_9__*,int /*<<< orphan*/  const*,size_t) ;TYPE_2__* priv; } ;
struct TYPE_11__ {size_t actual_offset; } ;
struct TYPE_10__ {int /*<<< orphan*/  async_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (size_t,int /*<<< orphan*/  const*,size_t) ; 
 size_t stub1 (TYPE_9__*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  vc_container_assert (int) ; 
 size_t vc_container_io_cache_flush (TYPE_3__*,TYPE_4__*,int) ; 

__attribute__((used)) static int32_t vc_container_io_cache_write( VC_CONTAINER_IO_T *p_ctx,
   VC_CONTAINER_IO_PRIVATE_CACHE_T *cache, const uint8_t *data, size_t size )
{
   int32_t written = 0;
   size_t bytes, ret;

   /* If we do not have a write cache then we need to flush it */
   if(cache->size && !cache->dirty)
   {
      ret = vc_container_io_cache_flush( p_ctx, cache, 1 );
      if(ret) return -(int32_t)ret;
   }

   while(size)
   {
      bytes = (cache->buffer_end - cache->buffer) - cache->position; /* Space left in cache */

      /* Flush the cache if it is full */
      if(!bytes)
      {
         /* Cache full, flush it */
         ret = vc_container_io_cache_flush( p_ctx, cache, 0 );
         if(ret)
         {
            written -= ret;
            return written;
         }
         continue;
      }

      if(bytes > size) bytes = size;

      if(!p_ctx->priv->async_io && bytes == cache->mem_size)
      {
         /* Write directly from the buffer */
         ret = cache->io->pf_write(cache->io, data + written, bytes);
         cache->offset += ret;
         cache->io->priv->actual_offset += ret;
      }
      else
      {
         /* Write in the cache */
         memcpy(cache->buffer + cache->position, data + written, bytes);
         cache->position += bytes;
         cache->dirty = 1;
         ret = bytes;
      }

      written += ret;
      if(ret != bytes) goto end;

      size -= bytes;
   }

 end:
   vc_container_assert(cache->offset + (int64_t)cache->position == p_ctx->offset + written);
   if(cache->position > cache->size) cache->size = cache->position;
   return written;
}