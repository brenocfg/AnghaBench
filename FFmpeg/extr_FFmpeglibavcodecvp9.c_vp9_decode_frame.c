#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_50__   TYPE_9__ ;
typedef  struct TYPE_49__   TYPE_8__ ;
typedef  struct TYPE_48__   TYPE_7__ ;
typedef  struct TYPE_47__   TYPE_6__ ;
typedef  struct TYPE_46__   TYPE_5__ ;
typedef  struct TYPE_45__   TYPE_4__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_27__ ;
typedef  struct TYPE_41__   TYPE_1__ ;
typedef  struct TYPE_40__   TYPE_14__ ;
typedef  struct TYPE_39__   TYPE_12__ ;
typedef  struct TYPE_38__   TYPE_11__ ;
typedef  struct TYPE_37__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_46__ {int tile_cols; } ;
struct TYPE_41__ {int /*<<< orphan*/  update_map; int /*<<< orphan*/  enabled; } ;
struct TYPE_48__ {int refreshrefmask; size_t framectxid; int txfmmode; int /*<<< orphan*/  invisible; scalar_t__ parallelmode; scalar_t__ refreshctx; TYPE_5__ tiling; scalar_t__ intraonly; scalar_t__ keyframe; int /*<<< orphan*/  errorres; TYPE_1__ segmentation; } ;
struct TYPE_49__ {TYPE_14__* frames; TYPE_7__ h; TYPE_27__* refs; } ;
struct TYPE_45__ {int /*<<< orphan*/  p; int /*<<< orphan*/ ***** coef; } ;
struct TYPE_50__ {int cols; int sb_cols; int ss_h; int pass; int active_tile_cols; TYPE_8__ s; TYPE_27__* next_refs; TYPE_6__* td; TYPE_4__ prob; TYPE_3__* prob_ctx; int /*<<< orphan*/  above_segpred_ctx; int /*<<< orphan*/ * above_uv_nnz_ctx; int /*<<< orphan*/  above_y_nnz_ctx; int /*<<< orphan*/  above_mode_ctx; int /*<<< orphan*/  above_skip_ctx; int /*<<< orphan*/  above_partition_ctx; } ;
typedef  TYPE_9__ VP9Context ;
struct TYPE_47__ {int /*<<< orphan*/  counts; int /*<<< orphan*/ * uveob_base; int /*<<< orphan*/ * uveob; int /*<<< orphan*/  eob_base; int /*<<< orphan*/  eob; int /*<<< orphan*/ * uvblock_base; int /*<<< orphan*/ * uvblock; int /*<<< orphan*/  block_base; int /*<<< orphan*/  block; int /*<<< orphan*/  b_base; int /*<<< orphan*/  b; } ;
struct TYPE_44__ {int /*<<< orphan*/  p; int /*<<< orphan*/ ***** coef; } ;
struct TYPE_43__ {int (* start_frame ) (TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int (* decode_slice ) (TYPE_12__*,int /*<<< orphan*/ *,int) ;int (* end_frame ) (TYPE_12__*) ;} ;
struct TYPE_42__ {TYPE_11__* f; } ;
struct TYPE_40__ {int uses_2pass; TYPE_27__ tf; scalar_t__ segmentation_map; } ;
struct TYPE_39__ {scalar_t__ active_thread_type; TYPE_2__* hwaccel; TYPE_9__* priv_data; } ;
struct TYPE_38__ {scalar_t__ width; scalar_t__ height; scalar_t__* buf; int /*<<< orphan*/  pict_type; scalar_t__ key_frame; int /*<<< orphan*/  pkt_dts; int /*<<< orphan*/  pts; } ;
struct TYPE_37__ {int size; int /*<<< orphan*/ * data; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; } ;
typedef  TYPE_10__ AVPacket ;
typedef  TYPE_11__ AVFrame ;
typedef  TYPE_12__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 size_t CUR_FRAME ; 
 int /*<<< orphan*/  DC_PRED ; 
 scalar_t__ FF_THREAD_FRAME ; 
 scalar_t__ FF_THREAD_SLICE ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  NEARESTMV ; 
 size_t REF_FRAME_MVPAIR ; 
 size_t REF_FRAME_SEGMAP ; 
 int av_frame_ref (void*,TYPE_11__*) ; 
 int /*<<< orphan*/  av_log (TYPE_12__*,int /*<<< orphan*/ ,char*,...) ; 
 int decode_frame_header (TYPE_12__*,int /*<<< orphan*/  const*,int,int*) ; 
 int decode_tiles (TYPE_12__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ff_thread_finish_setup (TYPE_12__*) ; 
 int ff_thread_ref_frame (TYPE_27__*,TYPE_27__*) ; 
 int /*<<< orphan*/  ff_thread_release_buffer (TYPE_12__*,TYPE_27__*) ; 
 int /*<<< orphan*/  ff_thread_report_progress (TYPE_27__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_vp9_adapt_probs (TYPE_9__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_12__*,int /*<<< orphan*/ *,int) ; 
 int stub3 (TYPE_12__*) ; 
 int update_block_buffers (TYPE_12__*) ; 
 int vp9_frame_alloc (TYPE_12__*,TYPE_14__*) ; 
 int vp9_frame_ref (TYPE_12__*,TYPE_14__*,TYPE_14__*) ; 
 int /*<<< orphan*/  vp9_frame_unref (TYPE_12__*,TYPE_14__*) ; 

__attribute__((used)) static int vp9_decode_frame(AVCodecContext *avctx, void *frame,
                            int *got_frame, AVPacket *pkt)
{
    const uint8_t *data = pkt->data;
    int size = pkt->size;
    VP9Context *s = avctx->priv_data;
    int ret, i, j, ref;
    int retain_segmap_ref = s->s.frames[REF_FRAME_SEGMAP].segmentation_map &&
                            (!s->s.h.segmentation.enabled || !s->s.h.segmentation.update_map);
    AVFrame *f;

    if ((ret = decode_frame_header(avctx, data, size, &ref)) < 0) {
        return ret;
    } else if (ret == 0) {
        if (!s->s.refs[ref].f->buf[0]) {
            av_log(avctx, AV_LOG_ERROR, "Requested reference %d not available\n", ref);
            return AVERROR_INVALIDDATA;
        }
        if ((ret = av_frame_ref(frame, s->s.refs[ref].f)) < 0)
            return ret;
        ((AVFrame *)frame)->pts = pkt->pts;
#if FF_API_PKT_PTS
FF_DISABLE_DEPRECATION_WARNINGS
        ((AVFrame *)frame)->pkt_pts = pkt->pts;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
        ((AVFrame *)frame)->pkt_dts = pkt->dts;
        for (i = 0; i < 8; i++) {
            if (s->next_refs[i].f->buf[0])
                ff_thread_release_buffer(avctx, &s->next_refs[i]);
            if (s->s.refs[i].f->buf[0] &&
                (ret = ff_thread_ref_frame(&s->next_refs[i], &s->s.refs[i])) < 0)
                return ret;
        }
        *got_frame = 1;
        return pkt->size;
    }
    data += ret;
    size -= ret;

    if (!retain_segmap_ref || s->s.h.keyframe || s->s.h.intraonly) {
        if (s->s.frames[REF_FRAME_SEGMAP].tf.f->buf[0])
            vp9_frame_unref(avctx, &s->s.frames[REF_FRAME_SEGMAP]);
        if (!s->s.h.keyframe && !s->s.h.intraonly && !s->s.h.errorres && s->s.frames[CUR_FRAME].tf.f->buf[0] &&
            (ret = vp9_frame_ref(avctx, &s->s.frames[REF_FRAME_SEGMAP], &s->s.frames[CUR_FRAME])) < 0)
            return ret;
    }
    if (s->s.frames[REF_FRAME_MVPAIR].tf.f->buf[0])
        vp9_frame_unref(avctx, &s->s.frames[REF_FRAME_MVPAIR]);
    if (!s->s.h.intraonly && !s->s.h.keyframe && !s->s.h.errorres && s->s.frames[CUR_FRAME].tf.f->buf[0] &&
        (ret = vp9_frame_ref(avctx, &s->s.frames[REF_FRAME_MVPAIR], &s->s.frames[CUR_FRAME])) < 0)
        return ret;
    if (s->s.frames[CUR_FRAME].tf.f->buf[0])
        vp9_frame_unref(avctx, &s->s.frames[CUR_FRAME]);
    if ((ret = vp9_frame_alloc(avctx, &s->s.frames[CUR_FRAME])) < 0)
        return ret;
    f = s->s.frames[CUR_FRAME].tf.f;
    f->key_frame = s->s.h.keyframe;
    f->pict_type = (s->s.h.keyframe || s->s.h.intraonly) ? AV_PICTURE_TYPE_I : AV_PICTURE_TYPE_P;

    if (s->s.frames[REF_FRAME_SEGMAP].tf.f->buf[0] &&
        (s->s.frames[REF_FRAME_MVPAIR].tf.f->width  != s->s.frames[CUR_FRAME].tf.f->width ||
         s->s.frames[REF_FRAME_MVPAIR].tf.f->height != s->s.frames[CUR_FRAME].tf.f->height)) {
        vp9_frame_unref(avctx, &s->s.frames[REF_FRAME_SEGMAP]);
    }

    // ref frame setup
    for (i = 0; i < 8; i++) {
        if (s->next_refs[i].f->buf[0])
            ff_thread_release_buffer(avctx, &s->next_refs[i]);
        if (s->s.h.refreshrefmask & (1 << i)) {
            ret = ff_thread_ref_frame(&s->next_refs[i], &s->s.frames[CUR_FRAME].tf);
        } else if (s->s.refs[i].f->buf[0]) {
            ret = ff_thread_ref_frame(&s->next_refs[i], &s->s.refs[i]);
        }
        if (ret < 0)
            return ret;
    }

    if (avctx->hwaccel) {
        ret = avctx->hwaccel->start_frame(avctx, NULL, 0);
        if (ret < 0)
            return ret;
        ret = avctx->hwaccel->decode_slice(avctx, pkt->data, pkt->size);
        if (ret < 0)
            return ret;
        ret = avctx->hwaccel->end_frame(avctx);
        if (ret < 0)
            return ret;
        goto finish;
    }

    // main tile decode loop
    memset(s->above_partition_ctx, 0, s->cols);
    memset(s->above_skip_ctx, 0, s->cols);
    if (s->s.h.keyframe || s->s.h.intraonly) {
        memset(s->above_mode_ctx, DC_PRED, s->cols * 2);
    } else {
        memset(s->above_mode_ctx, NEARESTMV, s->cols);
    }
    memset(s->above_y_nnz_ctx, 0, s->sb_cols * 16);
    memset(s->above_uv_nnz_ctx[0], 0, s->sb_cols * 16 >> s->ss_h);
    memset(s->above_uv_nnz_ctx[1], 0, s->sb_cols * 16 >> s->ss_h);
    memset(s->above_segpred_ctx, 0, s->cols);
    s->pass = s->s.frames[CUR_FRAME].uses_2pass =
        avctx->active_thread_type == FF_THREAD_FRAME && s->s.h.refreshctx && !s->s.h.parallelmode;
    if ((ret = update_block_buffers(avctx)) < 0) {
        av_log(avctx, AV_LOG_ERROR,
               "Failed to allocate block buffers\n");
        return ret;
    }
    if (s->s.h.refreshctx && s->s.h.parallelmode) {
        int j, k, l, m;

        for (i = 0; i < 4; i++) {
            for (j = 0; j < 2; j++)
                for (k = 0; k < 2; k++)
                    for (l = 0; l < 6; l++)
                        for (m = 0; m < 6; m++)
                            memcpy(s->prob_ctx[s->s.h.framectxid].coef[i][j][k][l][m],
                                   s->prob.coef[i][j][k][l][m], 3);
            if (s->s.h.txfmmode == i)
                break;
        }
        s->prob_ctx[s->s.h.framectxid].p = s->prob.p;
        ff_thread_finish_setup(avctx);
    } else if (!s->s.h.refreshctx) {
        ff_thread_finish_setup(avctx);
    }

#if HAVE_THREADS
    if (avctx->active_thread_type & FF_THREAD_SLICE) {
        for (i = 0; i < s->sb_rows; i++)
            atomic_store(&s->entries[i], 0);
    }
#endif

    do {
        for (i = 0; i < s->active_tile_cols; i++) {
            s->td[i].b = s->td[i].b_base;
            s->td[i].block = s->td[i].block_base;
            s->td[i].uvblock[0] = s->td[i].uvblock_base[0];
            s->td[i].uvblock[1] = s->td[i].uvblock_base[1];
            s->td[i].eob = s->td[i].eob_base;
            s->td[i].uveob[0] = s->td[i].uveob_base[0];
            s->td[i].uveob[1] = s->td[i].uveob_base[1];
        }

#if HAVE_THREADS
        if (avctx->active_thread_type == FF_THREAD_SLICE) {
            int tile_row, tile_col;

            av_assert1(!s->pass);

            for (tile_row = 0; tile_row < s->s.h.tiling.tile_rows; tile_row++) {
                for (tile_col = 0; tile_col < s->s.h.tiling.tile_cols; tile_col++) {
                    int64_t tile_size;

                    if (tile_col == s->s.h.tiling.tile_cols - 1 &&
                        tile_row == s->s.h.tiling.tile_rows - 1) {
                        tile_size = size;
                    } else {
                        tile_size = AV_RB32(data);
                        data += 4;
                        size -= 4;
                    }
                    if (tile_size > size)
                        return AVERROR_INVALIDDATA;
                    ret = ff_vp56_init_range_decoder(&s->td[tile_col].c_b[tile_row], data, tile_size);
                    if (ret < 0)
                        return ret;
                    if (vp56_rac_get_prob_branchy(&s->td[tile_col].c_b[tile_row], 128)) // marker bit
                        return AVERROR_INVALIDDATA;
                    data += tile_size;
                    size -= tile_size;
                }
            }

            ff_slice_thread_execute_with_mainfunc(avctx, decode_tiles_mt, loopfilter_proc, s->td, NULL, s->s.h.tiling.tile_cols);
        } else
#endif
        {
            ret = decode_tiles(avctx, data, size);
            if (ret < 0) {
                ff_thread_report_progress(&s->s.frames[CUR_FRAME].tf, INT_MAX, 0);
                return ret;
            }
        }

        // Sum all counts fields into td[0].counts for tile threading
        if (avctx->active_thread_type == FF_THREAD_SLICE)
            for (i = 1; i < s->s.h.tiling.tile_cols; i++)
                for (j = 0; j < sizeof(s->td[i].counts) / sizeof(unsigned); j++)
                    ((unsigned *)&s->td[0].counts)[j] += ((unsigned *)&s->td[i].counts)[j];

        if (s->pass < 2 && s->s.h.refreshctx && !s->s.h.parallelmode) {
            ff_vp9_adapt_probs(s);
            ff_thread_finish_setup(avctx);
        }
    } while (s->pass++ == 1);
    ff_thread_report_progress(&s->s.frames[CUR_FRAME].tf, INT_MAX, 0);

finish:
    // ref frame setup
    for (i = 0; i < 8; i++) {
        if (s->s.refs[i].f->buf[0])
            ff_thread_release_buffer(avctx, &s->s.refs[i]);
        if (s->next_refs[i].f->buf[0] &&
            (ret = ff_thread_ref_frame(&s->s.refs[i], &s->next_refs[i])) < 0)
            return ret;
    }

    if (!s->s.h.invisible) {
        if ((ret = av_frame_ref(frame, s->s.frames[CUR_FRAME].tf.f)) < 0)
            return ret;
        *got_frame = 1;
    }

    return pkt->size;
}