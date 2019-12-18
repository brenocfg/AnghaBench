#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t fset; int /*<<< orphan*/ * filterbuf; int /*<<< orphan*/ * filters; } ;
typedef  TYPE_1__ APEContext ;

/* Variables and functions */
 int APE_FILTER_LEVELS ; 
 int /*<<< orphan*/ ** ape_filter_orders ; 
 int init_entropy_decoder (TYPE_1__*) ; 
 int /*<<< orphan*/  init_filter (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_predictor_decoder (TYPE_1__*) ; 

__attribute__((used)) static int init_frame_decoder(APEContext *ctx)
{
    int i, ret;
    if ((ret = init_entropy_decoder(ctx)) < 0)
        return ret;
    init_predictor_decoder(ctx);

    for (i = 0; i < APE_FILTER_LEVELS; i++) {
        if (!ape_filter_orders[ctx->fset][i])
            break;
        init_filter(ctx, ctx->filters[i], ctx->filterbuf[i],
                    ape_filter_orders[ctx->fset][i]);
    }
    return 0;
}