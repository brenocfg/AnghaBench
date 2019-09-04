#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ current_field; TYPE_1__* csp; } ;
typedef  TYPE_3__ YADIFContext ;
struct TYPE_16__ {int parity; int tff; int w; int h; int plane; TYPE_6__* frame; } ;
typedef  TYPE_4__ ThreadData ;
struct TYPE_19__ {TYPE_2__* internal; TYPE_5__* priv; } ;
struct TYPE_18__ {int width; int height; } ;
struct TYPE_17__ {TYPE_3__ yadif; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* execute ) (TYPE_7__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {int nb_components; int /*<<< orphan*/  log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; } ;
typedef  TYPE_5__ BWDIFContext ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FFMIN (int,int /*<<< orphan*/ ) ; 
 scalar_t__ YADIF_FIELD_END ; 
 scalar_t__ YADIF_FIELD_NORMAL ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  ff_filter_get_nb_threads (TYPE_7__*) ; 
 int /*<<< orphan*/  filter_slice ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filter(AVFilterContext *ctx, AVFrame *dstpic,
                   int parity, int tff)
{
    BWDIFContext *bwdif = ctx->priv;
    YADIFContext *yadif = &bwdif->yadif;
    ThreadData td = { .frame = dstpic, .parity = parity, .tff = tff };
    int i;

    for (i = 0; i < yadif->csp->nb_components; i++) {
        int w = dstpic->width;
        int h = dstpic->height;

        if (i == 1 || i == 2) {
            w = AV_CEIL_RSHIFT(w, yadif->csp->log2_chroma_w);
            h = AV_CEIL_RSHIFT(h, yadif->csp->log2_chroma_h);
        }

        td.w     = w;
        td.h     = h;
        td.plane = i;

        ctx->internal->execute(ctx, filter_slice, &td, NULL, FFMIN(h, ff_filter_get_nb_threads(ctx)));
    }
    if (yadif->current_field == YADIF_FIELD_END) {
        yadif->current_field = YADIF_FIELD_NORMAL;
    }

    emms_c();
}