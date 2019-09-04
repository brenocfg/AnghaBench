#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_26__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_17__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  Vp3Fragment ;
struct TYPE_29__ {TYPE_26__* f; } ;
struct TYPE_30__ {int keyframe; int theora; scalar_t__* last_qps; scalar_t__* qps; int nqps; int skip_loop_filter; int fragment_count; int height; int* data_offset; int c_superblock_height; TYPE_17__ current_frame; TYPE_4__* avctx; scalar_t__ offset_y; scalar_t__ offset_x; scalar_t__ chroma_y_shift; scalar_t__ last_slice_end; scalar_t__ flipped_image; int /*<<< orphan*/  all_fragments; TYPE_17__ last_frame; TYPE_17__ golden_frame; void* version; scalar_t__ edge_emu_buffer; int /*<<< orphan*/ * filter_limit_values; } ;
typedef  TYPE_1__ Vp3DecodeContext ;
struct TYPE_34__ {int debug; scalar_t__ frame_number; scalar_t__ skip_loop_filter; scalar_t__ skip_frame; int active_thread_type; scalar_t__ height; scalar_t__ coded_height; scalar_t__ width; scalar_t__ coded_width; TYPE_1__* priv_data; } ;
struct TYPE_33__ {scalar_t__ crop_bottom; scalar_t__ crop_top; scalar_t__ crop_right; scalar_t__ crop_left; } ;
struct TYPE_32__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_31__ {int key_frame; int* linesize; void* pict_type; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AVDISCARD_ALL ; 
 scalar_t__ AVDISCARD_NONKEY ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 void* AV_PICTURE_TYPE_I ; 
 void* AV_PICTURE_TYPE_P ; 
 int FFABS (int) ; 
 int FF_DEBUG_PICT_INFO ; 
 int FF_THREAD_FRAME ; 
 int /*<<< orphan*/  HAVE_THREADS ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  apply_loop_filter (TYPE_1__*,int,int,int) ; 
 int av_frame_ref (void*,TYPE_26__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_26__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ av_malloc (int) ; 
 int /*<<< orphan*/  ff_thread_finish_setup (TYPE_4__*) ; 
 scalar_t__ ff_thread_get_buffer (TYPE_4__*,TYPE_17__*,int /*<<< orphan*/ ) ; 
 int ff_thread_ref_frame (TYPE_17__*,TYPE_17__*) ; 
 int /*<<< orphan*/  ff_thread_release_buffer (TYPE_4__*,TYPE_17__*) ; 
 int /*<<< orphan*/  ff_thread_report_progress (TYPE_17__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_dequantizer (TYPE_1__*,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  init_loop_filter (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  render_slice (TYPE_1__*,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ unpack_block_qpis (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ unpack_dct_coeffs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ unpack_modes (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ unpack_superblocks (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ unpack_vectors (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int update_frames (TYPE_4__*) ; 
 int /*<<< orphan*/  vp3_draw_horiz_band (TYPE_1__*,int) ; 

__attribute__((used)) static int vp3_decode_frame(AVCodecContext *avctx,
                            void *data, int *got_frame,
                            AVPacket *avpkt)
{
    AVFrame     *frame  = data;
    const uint8_t *buf  = avpkt->data;
    int buf_size        = avpkt->size;
    Vp3DecodeContext *s = avctx->priv_data;
    GetBitContext gb;
    int i, ret;

    if ((ret = init_get_bits8(&gb, buf, buf_size)) < 0)
        return ret;

#if CONFIG_THEORA_DECODER
    if (s->theora && get_bits1(&gb)) {
        int type = get_bits(&gb, 7);
        skip_bits_long(&gb, 6*8); /* "theora" */

        if (s->avctx->active_thread_type&FF_THREAD_FRAME) {
            av_log(avctx, AV_LOG_ERROR, "midstream reconfiguration with multithreading is unsupported, try -threads 1\n");
            return AVERROR_PATCHWELCOME;
        }
        if (type == 0) {
            vp3_decode_end(avctx);
            ret = theora_decode_header(avctx, &gb);

            if (ret >= 0)
                ret = vp3_decode_init(avctx);
            if (ret < 0) {
                vp3_decode_end(avctx);
                return ret;
            }
            return buf_size;
        } else if (type == 2) {
            vp3_decode_end(avctx);
            ret = theora_decode_tables(avctx, &gb);
            if (ret >= 0)
                ret = vp3_decode_init(avctx);
            if (ret < 0) {
                vp3_decode_end(avctx);
                return ret;
            }
            return buf_size;
        }

        av_log(avctx, AV_LOG_ERROR,
               "Header packet passed to frame decoder, skipping\n");
        return -1;
    }
#endif

    s->keyframe = !get_bits1(&gb);
    if (!s->all_fragments) {
        av_log(avctx, AV_LOG_ERROR, "Data packet without prior valid headers\n");
        return -1;
    }
    if (!s->theora)
        skip_bits(&gb, 1);
    for (i = 0; i < 3; i++)
        s->last_qps[i] = s->qps[i];

    s->nqps = 0;
    do {
        s->qps[s->nqps++] = get_bits(&gb, 6);
    } while (s->theora >= 0x030200 && s->nqps < 3 && get_bits1(&gb));
    for (i = s->nqps; i < 3; i++)
        s->qps[i] = -1;

    if (s->avctx->debug & FF_DEBUG_PICT_INFO)
        av_log(s->avctx, AV_LOG_INFO, " VP3 %sframe #%d: Q index = %d\n",
               s->keyframe ? "key" : "", avctx->frame_number + 1, s->qps[0]);

    s->skip_loop_filter = !s->filter_limit_values[s->qps[0]] ||
                          avctx->skip_loop_filter >= (s->keyframe ? AVDISCARD_ALL
                                                                  : AVDISCARD_NONKEY);

    if (s->qps[0] != s->last_qps[0])
        init_loop_filter(s);

    for (i = 0; i < s->nqps; i++)
        // reinit all dequantizers if the first one changed, because
        // the DC of the first quantizer must be used for all matrices
        if (s->qps[i] != s->last_qps[i] || s->qps[0] != s->last_qps[0])
            init_dequantizer(s, i);

    if (avctx->skip_frame >= AVDISCARD_NONKEY && !s->keyframe)
        return buf_size;

    s->current_frame.f->pict_type = s->keyframe ? AV_PICTURE_TYPE_I
                                                : AV_PICTURE_TYPE_P;
    s->current_frame.f->key_frame = s->keyframe;
    if (ff_thread_get_buffer(avctx, &s->current_frame, AV_GET_BUFFER_FLAG_REF) < 0)
        goto error;

    if (!s->edge_emu_buffer)
        s->edge_emu_buffer = av_malloc(9 * FFABS(s->current_frame.f->linesize[0]));

    if (s->keyframe) {
        if (!s->theora) {
            skip_bits(&gb, 4); /* width code */
            skip_bits(&gb, 4); /* height code */
            if (s->version) {
                s->version = get_bits(&gb, 5);
                if (avctx->frame_number == 0)
                    av_log(s->avctx, AV_LOG_DEBUG,
                           "VP version: %d\n", s->version);
            }
        }
        if (s->version || s->theora) {
            if (get_bits1(&gb))
                av_log(s->avctx, AV_LOG_ERROR,
                       "Warning, unsupported keyframe coding type?!\n");
            skip_bits(&gb, 2); /* reserved? */
        }
    } else {
        if (!s->golden_frame.f->data[0]) {
            av_log(s->avctx, AV_LOG_WARNING,
                   "vp3: first frame not a keyframe\n");

            s->golden_frame.f->pict_type = AV_PICTURE_TYPE_I;
            if (ff_thread_get_buffer(avctx, &s->golden_frame,
                                     AV_GET_BUFFER_FLAG_REF) < 0)
                goto error;
            ff_thread_release_buffer(avctx, &s->last_frame);
            if ((ret = ff_thread_ref_frame(&s->last_frame,
                                           &s->golden_frame)) < 0)
                goto error;
            ff_thread_report_progress(&s->last_frame, INT_MAX, 0);
        }
    }

    memset(s->all_fragments, 0, s->fragment_count * sizeof(Vp3Fragment));
    ff_thread_finish_setup(avctx);

    if (unpack_superblocks(s, &gb)) {
        av_log(s->avctx, AV_LOG_ERROR, "error in unpack_superblocks\n");
        goto error;
    }
    if (unpack_modes(s, &gb)) {
        av_log(s->avctx, AV_LOG_ERROR, "error in unpack_modes\n");
        goto error;
    }
    if (unpack_vectors(s, &gb)) {
        av_log(s->avctx, AV_LOG_ERROR, "error in unpack_vectors\n");
        goto error;
    }
    if (unpack_block_qpis(s, &gb)) {
        av_log(s->avctx, AV_LOG_ERROR, "error in unpack_block_qpis\n");
        goto error;
    }
    if (unpack_dct_coeffs(s, &gb)) {
        av_log(s->avctx, AV_LOG_ERROR, "error in unpack_dct_coeffs\n");
        goto error;
    }

    for (i = 0; i < 3; i++) {
        int height = s->height >> (i && s->chroma_y_shift);
        if (s->flipped_image)
            s->data_offset[i] = 0;
        else
            s->data_offset[i] = (height - 1) * s->current_frame.f->linesize[i];
    }

    s->last_slice_end = 0;
    for (i = 0; i < s->c_superblock_height; i++)
        render_slice(s, i);

    // filter the last row
    for (i = 0; i < 3; i++) {
        int row = (s->height >> (3 + (i && s->chroma_y_shift))) - 1;
        apply_loop_filter(s, i, row, row + 1);
    }
    vp3_draw_horiz_band(s, s->height);

    /* output frame, offset as needed */
    if ((ret = av_frame_ref(data, s->current_frame.f)) < 0)
        return ret;

    frame->crop_left   = s->offset_x;
    frame->crop_right  = avctx->coded_width - avctx->width - s->offset_x;
    frame->crop_top    = s->offset_y;
    frame->crop_bottom = avctx->coded_height - avctx->height - s->offset_y;

    *got_frame = 1;

    if (!HAVE_THREADS || !(s->avctx->active_thread_type & FF_THREAD_FRAME)) {
        ret = update_frames(avctx);
        if (ret < 0)
            return ret;
    }

    return buf_size;

error:
    ff_thread_report_progress(&s->current_frame, INT_MAX, 0);

    if (!HAVE_THREADS || !(s->avctx->active_thread_type & FF_THREAD_FRAME))
        av_frame_unref(s->current_frame.f);

    return -1;
}