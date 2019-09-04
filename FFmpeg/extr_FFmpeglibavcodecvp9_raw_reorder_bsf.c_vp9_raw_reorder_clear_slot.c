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
struct TYPE_4__ {TYPE_2__** slot; } ;
typedef  TYPE_1__ VP9RawReorderContext ;
struct TYPE_5__ {int slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  vp9_raw_reorder_frame_free (TYPE_2__**) ; 

__attribute__((used)) static void vp9_raw_reorder_clear_slot(VP9RawReorderContext *ctx, int s)
{
    if (ctx->slot[s]) {
        ctx->slot[s]->slots &= ~(1 << s);
        if (ctx->slot[s]->slots == 0)
            vp9_raw_reorder_frame_free(&ctx->slot[s]);
        else
            ctx->slot[s] = NULL;
    }
}