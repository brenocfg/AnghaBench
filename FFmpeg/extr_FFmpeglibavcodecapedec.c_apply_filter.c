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
struct TYPE_4__ {int /*<<< orphan*/  fileversion; } ;
typedef  int /*<<< orphan*/  APEFilter ;
typedef  TYPE_1__ APEContext ;

/* Variables and functions */
 int /*<<< orphan*/  do_apply_filter (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void apply_filter(APEContext *ctx, APEFilter *f,
                         int32_t *data0, int32_t *data1,
                         int count, int order, int fracbits)
{
    do_apply_filter(ctx, ctx->fileversion, &f[0], data0, count, order, fracbits);
    if (data1)
        do_apply_filter(ctx, ctx->fileversion, &f[1], data1, count, order, fracbits);
}