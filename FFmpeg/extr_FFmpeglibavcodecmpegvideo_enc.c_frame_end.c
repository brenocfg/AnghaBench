#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int log2_chroma_w; int log2_chroma_h; } ;
struct TYPE_14__ {TYPE_3__* f; scalar_t__ reference; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* draw_edges ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ;} ;
struct TYPE_17__ {int h_edge_pos; int v_edge_pos; size_t last_pict_type; size_t pict_type; size_t last_non_b_pict_type; TYPE_6__* current_picture_ptr; int /*<<< orphan*/ * last_lambda_for; TYPE_4__ current_picture; TYPE_2__ mpvencdsp; TYPE_1__* avctx; int /*<<< orphan*/  intra_only; scalar_t__ unrestricted_mv; } ;
struct TYPE_16__ {TYPE_5__* f; } ;
struct TYPE_15__ {int /*<<< orphan*/  quality; } ;
struct TYPE_13__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {int /*<<< orphan*/  pix_fmt; } ;
typedef  TYPE_7__ MpegEncContext ;
typedef  TYPE_8__ AVPixFmtDescriptor ;

/* Variables and functions */
 size_t AV_PICTURE_TYPE_B ; 
 int EDGE_BOTTOM ; 
 int EDGE_TOP ; 
 int EDGE_WIDTH ; 
 TYPE_8__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 

__attribute__((used)) static void frame_end(MpegEncContext *s)
{
    if (s->unrestricted_mv &&
        s->current_picture.reference &&
        !s->intra_only) {
        const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(s->avctx->pix_fmt);
        int hshift = desc->log2_chroma_w;
        int vshift = desc->log2_chroma_h;
        s->mpvencdsp.draw_edges(s->current_picture.f->data[0],
                                s->current_picture.f->linesize[0],
                                s->h_edge_pos, s->v_edge_pos,
                                EDGE_WIDTH, EDGE_WIDTH,
                                EDGE_TOP | EDGE_BOTTOM);
        s->mpvencdsp.draw_edges(s->current_picture.f->data[1],
                                s->current_picture.f->linesize[1],
                                s->h_edge_pos >> hshift,
                                s->v_edge_pos >> vshift,
                                EDGE_WIDTH >> hshift,
                                EDGE_WIDTH >> vshift,
                                EDGE_TOP | EDGE_BOTTOM);
        s->mpvencdsp.draw_edges(s->current_picture.f->data[2],
                                s->current_picture.f->linesize[2],
                                s->h_edge_pos >> hshift,
                                s->v_edge_pos >> vshift,
                                EDGE_WIDTH >> hshift,
                                EDGE_WIDTH >> vshift,
                                EDGE_TOP | EDGE_BOTTOM);
    }

    emms_c();

    s->last_pict_type                 = s->pict_type;
    s->last_lambda_for [s->pict_type] = s->current_picture_ptr->f->quality;
    if (s->pict_type!= AV_PICTURE_TYPE_B)
        s->last_non_b_pict_type = s->pict_type;

#if FF_API_CODED_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    av_frame_unref(s->avctx->coded_frame);
    av_frame_copy_props(s->avctx->coded_frame, s->current_picture.f);
FF_ENABLE_DEPRECATION_WARNINGS
#endif
#if FF_API_ERROR_FRAME
FF_DISABLE_DEPRECATION_WARNINGS
    memcpy(s->current_picture.f->error, s->current_picture.encoding_error,
           sizeof(s->current_picture.encoding_error));
FF_ENABLE_DEPRECATION_WARNINGS
#endif
}