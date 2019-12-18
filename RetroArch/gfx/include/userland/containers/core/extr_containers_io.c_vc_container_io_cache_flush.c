#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_IO_T ;
struct TYPE_14__ {size_t position; size_t size; size_t offset; scalar_t__ mem_size; scalar_t__ mem_max_size; scalar_t__ mem; scalar_t__ buffer; scalar_t__ dirty; TYPE_7__* io; } ;
typedef  TYPE_4__ VC_CONTAINER_IO_PRIVATE_CACHE_T ;
struct TYPE_15__ {scalar_t__ (* pf_seek ) (TYPE_7__*,size_t) ;size_t (* pf_write ) (TYPE_7__*,scalar_t__,size_t) ;TYPE_2__* priv; } ;
struct TYPE_12__ {size_t actual_offset; } ;
struct TYPE_11__ {size_t actual_offset; scalar_t__ async_io; } ;

/* Variables and functions */
 int MEM_CACHE_ALIGNMENT ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ async_io_wait_complete (scalar_t__,TYPE_4__*,int) ; 
 size_t async_io_write (scalar_t__,TYPE_4__*) ; 
 scalar_t__ stub1 (TYPE_7__*,size_t) ; 
 size_t stub2 (TYPE_7__*,scalar_t__,size_t) ; 

__attribute__((used)) static size_t vc_container_io_cache_flush( VC_CONTAINER_IO_T *p_ctx,
   VC_CONTAINER_IO_PRIVATE_CACHE_T *cache, int complete )
{
   size_t ret = 0, shift;

   if(cache->position > cache->size) cache->size = cache->position;

   if(cache->dirty && cache->size)
   {
      if(p_ctx->priv->actual_offset != cache->offset)
      {
         if(p_ctx->priv->async_io) async_io_wait_complete( p_ctx->priv->async_io, cache, complete );

         if(cache->io->pf_seek(cache->io, cache->offset) != VC_CONTAINER_SUCCESS)
            return 0;
      }

      if(p_ctx->priv->async_io)
      {
         ret = async_io_write( p_ctx->priv->async_io, cache );
         if(async_io_wait_complete( p_ctx->priv->async_io, cache, complete ) != VC_CONTAINER_SUCCESS)
            ret = 0;
      }
      else
         ret = cache->io->pf_write(cache->io, cache->buffer, cache->size);

      cache->io->priv->actual_offset = cache->offset + ret;
      ret = cache->position - ret;
   }
   cache->dirty = 0;

   cache->offset += cache->size;
   if(cache->mem_size == cache->mem_max_size)
   {
      shift = cache->offset &(MEM_CACHE_ALIGNMENT-1);
      cache->buffer = cache->mem + shift;
   }

   cache->position = cache->size = 0;
   return ret;
}