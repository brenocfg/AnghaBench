#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int valid_ids; scalar_t__ nb_filter_buffers; void** filter_buffers; void* va_context; void* va_config; } ;
typedef  TYPE_1__ VAAPIVPPContext ;
struct TYPE_5__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int VAProcFilterCount ; 
 void* VA_INVALID_ID ; 

void ff_vaapi_vpp_ctx_init(AVFilterContext *avctx)
{
    int i;
    VAAPIVPPContext *ctx   = avctx->priv;

    ctx->va_config  = VA_INVALID_ID;
    ctx->va_context = VA_INVALID_ID;
    ctx->valid_ids  = 1;

    for (i = 0; i < VAProcFilterCount; i++)
        ctx->filter_buffers[i] = VA_INVALID_ID;
    ctx->nb_filter_buffers = 0;
}