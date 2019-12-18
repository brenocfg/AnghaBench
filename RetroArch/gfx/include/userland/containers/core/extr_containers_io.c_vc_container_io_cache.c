#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_7__ {int capabilities; size_t (* pf_read ) (TYPE_1__*,scalar_t__,size_t) ;TYPE_2__* priv; scalar_t__ offset; } ;
typedef  TYPE_1__ VC_CONTAINER_IO_T ;
struct TYPE_8__ {size_t cached_areas_num; scalar_t__ actual_offset; TYPE_3__* cache; TYPE_3__* cached_areas; } ;
typedef  TYPE_2__ VC_CONTAINER_IO_PRIVATE_T ;
struct TYPE_9__ {scalar_t__ position; scalar_t__ size; size_t mem_max_size; size_t mem_size; scalar_t__ mem; scalar_t__ buffer; scalar_t__ buffer_end; scalar_t__ end; scalar_t__ offset; TYPE_1__* io; scalar_t__ start; } ;
typedef  TYPE_3__ VC_CONTAINER_IO_PRIVATE_CACHE_T ;

/* Variables and functions */
 size_t MAX_NUM_CACHED_AREAS ; 
 size_t MEM_CACHE_AREA_READ_MAX_SIZE ; 
 size_t MEM_CACHE_READ_MAX_SIZE ; 
 int VC_CONTAINER_IO_CAPS_CANT_SEEK ; 
 int VC_CONTAINER_IO_CAPS_SEEK_SLOW ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,size_t) ; 
 size_t stub1 (TYPE_1__*,scalar_t__,size_t) ; 
 scalar_t__ vc_container_io_seek (TYPE_1__*,scalar_t__) ; 

size_t vc_container_io_cache(VC_CONTAINER_IO_T *p_ctx, size_t size)
{
   VC_CONTAINER_IO_PRIVATE_T *private = p_ctx->priv;
   VC_CONTAINER_IO_PRIVATE_CACHE_T *cache, *main_cache;
   VC_CONTAINER_STATUS_T status;

   /* Sanity checking */
   if(private->cached_areas_num >= MAX_NUM_CACHED_AREAS) return 0;

   cache = &private->cached_areas[private->cached_areas_num];
   cache->start = p_ctx->offset;
   cache->end = cache->start + size;
   cache->offset = p_ctx->offset;
   cache->position = 0;
   cache->size = 0;
   cache->io = p_ctx;

   /* Set the size of the cache area depending on the capabilities of the i/o */
   if(p_ctx->capabilities & VC_CONTAINER_IO_CAPS_CANT_SEEK)
      cache->mem_max_size = MEM_CACHE_AREA_READ_MAX_SIZE;
   else if((p_ctx->capabilities & VC_CONTAINER_IO_CAPS_SEEK_SLOW) &&
           size <= MEM_CACHE_AREA_READ_MAX_SIZE)
      cache->mem_max_size = MEM_CACHE_AREA_READ_MAX_SIZE;
   else
      cache->mem_max_size = MEM_CACHE_READ_MAX_SIZE;

   cache->mem_size = size;
   if(cache->mem_size > cache->mem_max_size) cache->mem_size = cache->mem_max_size;
   cache->mem = malloc(cache->mem_size);

   cache->buffer = cache->mem;
   cache->buffer_end = cache->mem + cache->mem_size;

   if(!cache->mem) return 0;
   private->cached_areas_num++;

   /* Copy any data we've got in the current cache into the new cache */
   main_cache = p_ctx->priv->cache;
   if(main_cache && main_cache->position < main_cache->size)
   {
      cache->size = main_cache->size - main_cache->position;
      if(cache->size > cache->mem_size) cache->size = cache->mem_size;
      memcpy(cache->buffer, main_cache->buffer + main_cache->position, cache->size);
      main_cache->position += cache->size;
   }

   /* Read the rest of the cache directly from the stream */
   if(cache->mem_size > cache->size)
   {
      size_t ret = cache->io->pf_read(cache->io, cache->buffer + cache->size,
                                      cache->mem_size - cache->size);
      cache->size += ret;
      cache->io->priv->actual_offset = cache->offset + cache->size;
   }

   status = vc_container_io_seek(p_ctx, cache->end);
   if(status != VC_CONTAINER_SUCCESS)
      return 0;

   if(p_ctx->capabilities & VC_CONTAINER_IO_CAPS_CANT_SEEK)
      return cache->size;
   else
      return size;
}