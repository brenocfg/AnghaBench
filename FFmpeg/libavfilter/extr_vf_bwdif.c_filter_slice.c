#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_19__ {scalar_t__ current_field; TYPE_6__* cur; TYPE_4__* next; TYPE_3__* prev; TYPE_2__* csp; } ;
typedef  TYPE_7__ YADIFContext ;
struct TYPE_20__ {size_t plane; int h; int parity; int w; int tff; TYPE_5__* frame; } ;
typedef  TYPE_8__ ThreadData ;
struct TYPE_21__ {int /*<<< orphan*/  (* filter_line ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int,int,int,int) ;int /*<<< orphan*/  (* filter_edge ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int) ;int /*<<< orphan*/  (* filter_intra ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int) ;TYPE_7__ yadif; } ;
struct TYPE_18__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_17__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_16__ {int /*<<< orphan*/ ** data; } ;
struct TYPE_15__ {int /*<<< orphan*/ ** data; } ;
struct TYPE_14__ {TYPE_1__* comp; } ;
struct TYPE_13__ {int depth; } ;
struct TYPE_12__ {TYPE_9__* priv; } ;
typedef  TYPE_9__ BWDIFContext ;
typedef  TYPE_10__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ YADIF_FIELD_END ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static int filter_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    BWDIFContext *s = ctx->priv;
    YADIFContext *yadif = &s->yadif;
    ThreadData *td  = arg;
    int linesize = yadif->cur->linesize[td->plane];
    int clip_max = (1 << (yadif->csp->comp[td->plane].depth)) - 1;
    int df = (yadif->csp->comp[td->plane].depth + 7) / 8;
    int refs = linesize / df;
    int slice_start = (td->h *  jobnr   ) / nb_jobs;
    int slice_end   = (td->h * (jobnr+1)) / nb_jobs;
    int y;

    for (y = slice_start; y < slice_end; y++) {
        if ((y ^ td->parity) & 1) {
            uint8_t *prev = &yadif->prev->data[td->plane][y * linesize];
            uint8_t *cur  = &yadif->cur ->data[td->plane][y * linesize];
            uint8_t *next = &yadif->next->data[td->plane][y * linesize];
            uint8_t *dst  = &td->frame->data[td->plane][y * td->frame->linesize[td->plane]];
            if (yadif->current_field == YADIF_FIELD_END) {
                s->filter_intra(dst, cur, td->w, (y + df) < td->h ? refs : -refs,
                                y > (df - 1) ? -refs : refs,
                                (y + 3*df) < td->h ? 3 * refs : -refs,
                                y > (3*df - 1) ? -3 * refs : refs,
                                td->parity ^ td->tff, clip_max);
            } else if ((y < 4) || ((y + 5) > td->h)) {
                s->filter_edge(dst, prev, cur, next, td->w,
                               (y + df) < td->h ? refs : -refs,
                               y > (df - 1) ? -refs : refs,
                               refs << 1, -(refs << 1),
                               td->parity ^ td->tff, clip_max,
                               (y < 2) || ((y + 3) > td->h) ? 0 : 1);
            } else {
                s->filter_line(dst, prev, cur, next, td->w,
                               refs, -refs, refs << 1, -(refs << 1),
                               3 * refs, -3 * refs, refs << 2, -(refs << 2),
                               td->parity ^ td->tff, clip_max);
            }
        } else {
            memcpy(&td->frame->data[td->plane][y * td->frame->linesize[td->plane]],
                   &yadif->cur->data[td->plane][y * linesize], td->w * df);
        }
    }
    return 0;
}