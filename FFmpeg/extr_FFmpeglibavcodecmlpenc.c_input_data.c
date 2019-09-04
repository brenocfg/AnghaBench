#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* avctx; } ;
struct TYPE_5__ {scalar_t__ sample_fmt; } ;
typedef  TYPE_2__ MLPEncodeContext ;

/* Variables and functions */
 scalar_t__ AV_SAMPLE_FMT_S32 ; 
 int /*<<< orphan*/  input_data_internal (TYPE_2__*,void*,int) ; 

__attribute__((used)) static void input_data(MLPEncodeContext *ctx, void *samples)
{
    if (ctx->avctx->sample_fmt == AV_SAMPLE_FMT_S32)
        input_data_internal(ctx, samples, 1);
    else
        input_data_internal(ctx, samples, 0);
}