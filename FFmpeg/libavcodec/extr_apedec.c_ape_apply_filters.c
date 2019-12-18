#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {size_t fset; int /*<<< orphan*/ * filters; } ;
typedef  TYPE_1__ APEContext ;

/* Variables and functions */
 int APE_FILTER_LEVELS ; 
 int /*<<< orphan*/ ** ape_filter_fracbits ; 
 int /*<<< orphan*/ ** ape_filter_orders ; 
 int /*<<< orphan*/  apply_filter (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ape_apply_filters(APEContext *ctx, int32_t *decoded0,
                              int32_t *decoded1, int count)
{
    int i;

    for (i = 0; i < APE_FILTER_LEVELS; i++) {
        if (!ape_filter_orders[ctx->fset][i])
            break;
        apply_filter(ctx, ctx->filters[i], decoded0, decoded1, count,
                     ape_filter_orders[ctx->fset][i],
                     ape_filter_fracbits[ctx->fset][i]);
    }
}