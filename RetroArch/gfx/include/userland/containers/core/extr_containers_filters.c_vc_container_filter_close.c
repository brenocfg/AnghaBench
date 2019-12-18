#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_8__ {TYPE_1__* priv; int /*<<< orphan*/  (* pf_close ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ VC_CONTAINER_FILTER_T ;
struct TYPE_7__ {scalar_t__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  vc_container_filter_unload (TYPE_2__*) ; 

VC_CONTAINER_STATUS_T vc_container_filter_close( VC_CONTAINER_FILTER_T *p_ctx )
{
   if (p_ctx)
   {
      if(p_ctx->pf_close) p_ctx->pf_close(p_ctx);
      if(p_ctx->priv && p_ctx->priv->handle) vc_container_filter_unload(p_ctx);
      free(p_ctx);
   }
   return VC_CONTAINER_SUCCESS;
}