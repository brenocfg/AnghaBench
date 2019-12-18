#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_11__ {int /*<<< orphan*/  uri_parts; int /*<<< orphan*/  (* pf_close ) (TYPE_3__*) ;TYPE_2__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_IO_T ;
struct TYPE_12__ {TYPE_3__* mem; scalar_t__ dirty; } ;
struct TYPE_10__ {unsigned int cached_areas_num; TYPE_1__* cached_areas; TYPE_6__ caches; scalar_t__ caches_num; scalar_t__ async_io; } ;
struct TYPE_9__ {TYPE_3__* mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  async_io_stop (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  vc_container_io_cache_flush (TYPE_3__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  vc_uri_release (int /*<<< orphan*/ ) ; 

VC_CONTAINER_STATUS_T vc_container_io_close( VC_CONTAINER_IO_T *p_ctx )
{
   unsigned int i;

   if(p_ctx)
   {
      if(p_ctx->priv)
      {
         if(p_ctx->priv->caches_num)
         {
            if(p_ctx->priv->caches.dirty)
               vc_container_io_cache_flush( p_ctx, &p_ctx->priv->caches, 1 );
         }

         if(p_ctx->priv->async_io)
            async_io_stop( p_ctx->priv->async_io );
         else if(p_ctx->priv->caches_num)
            free(p_ctx->priv->caches.mem);

         for(i = 0; i < p_ctx->priv->cached_areas_num; i++)
            free(p_ctx->priv->cached_areas[i].mem);

         if(p_ctx->pf_close)
            p_ctx->pf_close(p_ctx);
      }
      vc_uri_release(p_ctx->uri_parts);
      free(p_ctx);
   }
   return VC_CONTAINER_SUCCESS;
}