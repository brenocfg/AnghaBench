#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_52__   TYPE_9__ ;
typedef  struct TYPE_51__   TYPE_8__ ;
typedef  struct TYPE_50__   TYPE_7__ ;
typedef  struct TYPE_49__   TYPE_6__ ;
typedef  struct TYPE_48__   TYPE_5__ ;
typedef  struct TYPE_47__   TYPE_4__ ;
typedef  struct TYPE_46__   TYPE_3__ ;
typedef  struct TYPE_45__   TYPE_32__ ;
typedef  struct TYPE_44__   TYPE_30__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_21__ ;
typedef  struct TYPE_41__   TYPE_1__ ;
typedef  struct TYPE_40__   TYPE_19__ ;
typedef  struct TYPE_39__   TYPE_18__ ;
typedef  struct TYPE_38__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_52__ {int flags2; int active_thread_type; scalar_t__ skip_frame; int err_recognition; int debug; TYPE_2__* hwaccel; int /*<<< orphan*/  codec_id; } ;
struct TYPE_51__ {scalar_t__ ref_idc; int type; int* data; int /*<<< orphan*/  size_bits; int /*<<< orphan*/  gb; int /*<<< orphan*/  raw_size; int /*<<< orphan*/  raw_data; } ;
struct TYPE_39__ {int /*<<< orphan*/  tf; int /*<<< orphan*/  reference; TYPE_5__* f; } ;
struct TYPE_42__ {TYPE_4__* pps; TYPE_3__** sps_list; int /*<<< orphan*/  const* sps; } ;
struct TYPE_41__ {int recovery_frame_cnt; } ;
struct TYPE_40__ {int /*<<< orphan*/  green_metadata; TYPE_1__ recovery_point; } ;
struct TYPE_44__ {int nb_nals; TYPE_8__* nals; } ;
struct TYPE_50__ {int has_slice; int nal_unit_type; int current_slice; int nal_length_size; int is_avc; scalar_t__ nal_ref_idc; int has_recovery_point; int nb_slice_ctx_queued; int setup_finished; int nb_slice_ctx; scalar_t__ picture_structure; TYPE_18__* cur_pic_ptr; int /*<<< orphan*/  droppable; TYPE_18__ last_pic_for_ec; TYPE_6__* slice_ctx; scalar_t__ enable_er; TYPE_21__ ps; TYPE_9__* avctx; TYPE_19__ sei; int /*<<< orphan*/  next_outputed_poc; TYPE_30__ pkt; int /*<<< orphan*/  first_field; } ;
struct TYPE_45__ {scalar_t__ ref_count; int /*<<< orphan*/  next_pic; int /*<<< orphan*/  last_pic; int /*<<< orphan*/  cur_pic; scalar_t__ error_occurred; } ;
struct TYPE_49__ {TYPE_14__** ref_list; TYPE_32__ er; scalar_t__* ref_count; } ;
struct TYPE_48__ {int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; scalar_t__* buf; int /*<<< orphan*/  decode_error_flags; } ;
struct TYPE_47__ {size_t sps_id; } ;
struct TYPE_46__ {scalar_t__ data; } ;
struct TYPE_43__ {int (* start_frame ) (TYPE_9__*,int /*<<< orphan*/  const*,int) ;int (* decode_slice ) (TYPE_9__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* decode_params ) (TYPE_9__* const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_38__ {TYPE_18__* parent; int /*<<< orphan*/  reference; int /*<<< orphan*/  linesize; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  SPS ;
typedef  TYPE_6__ H264SliceContext ;
typedef  TYPE_7__ H264Context ;
typedef  TYPE_8__ H2645NAL ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_9__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AVDISCARD_NONREF ; 
 int AV_CODEC_FLAG2_CHUNKS ; 
 int AV_CODEC_FLAG2_FAST ; 
 int AV_EF_EXPLODE ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 unsigned int AV_RB32 (int /*<<< orphan*/  const*) ; 
 int FF_DEBUG_GREEN_MD ; 
 int /*<<< orphan*/  FF_DECODE_ERROR_DECODE_SLICES ; 
 int FF_THREAD_FRAME ; 
 int /*<<< orphan*/  FIELD_PICTURE (TYPE_7__*) ; 
#define  H264_NAL_AUD 141 
#define  H264_NAL_AUXILIARY_SLICE 140 
#define  H264_NAL_DPA 139 
#define  H264_NAL_DPB 138 
#define  H264_NAL_DPC 137 
#define  H264_NAL_END_SEQUENCE 136 
#define  H264_NAL_END_STREAM 135 
#define  H264_NAL_FILLER_DATA 134 
#define  H264_NAL_IDR_SLICE 133 
#define  H264_NAL_PPS 132 
#define  H264_NAL_SEI 131 
#define  H264_NAL_SLICE 130 
#define  H264_NAL_SPS 129 
#define  H264_NAL_SPS_EXT 128 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  INT_MIN ; 
 scalar_t__ PICT_BOTTOM_FIELD ; 
 int /*<<< orphan*/  av_log (TYPE_9__* const,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_9__* const,char*) ; 
 int /*<<< orphan*/  debug_green_metadata (int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  ff_er_frame_end (TYPE_32__*) ; 
 int ff_h2645_packet_split (TYPE_30__*,int /*<<< orphan*/  const*,int,TYPE_9__* const,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ff_h264_decode_picture_parameter_set (int /*<<< orphan*/ *,TYPE_9__* const,TYPE_21__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_h264_decode_seq_parameter_set (int /*<<< orphan*/ *,TYPE_9__* const,TYPE_21__*,int) ; 
 int ff_h264_execute_decode_slices (TYPE_7__*) ; 
 int ff_h264_queue_decode_slice (TYPE_7__*,TYPE_8__*) ; 
 int ff_h264_sei_decode (TYPE_19__*,int /*<<< orphan*/ *,TYPE_21__*,TYPE_9__* const) ; 
 int /*<<< orphan*/  ff_h264_sei_uninit (TYPE_19__*) ; 
 int /*<<< orphan*/  ff_h264_set_erpic (int /*<<< orphan*/ *,TYPE_18__*) ; 
 int /*<<< orphan*/  ff_thread_finish_setup (TYPE_9__* const) ; 
 int /*<<< orphan*/  ff_thread_report_progress (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int get_last_needed_nal (TYPE_7__*) ; 
 int /*<<< orphan*/  idr (TYPE_7__*) ; 
 int /*<<< orphan*/  init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_14__*,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_9__*,int /*<<< orphan*/  const*,int) ; 
 int stub2 (TYPE_9__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (TYPE_9__* const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub4 (TYPE_9__* const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_nal_units(H264Context *h, const uint8_t *buf, int buf_size)
{
    AVCodecContext *const avctx = h->avctx;
    int nals_needed = 0; ///< number of NALs that need decoding before the next frame thread starts
    int idr_cleared=0;
    int i, ret = 0;

    h->has_slice = 0;
    h->nal_unit_type= 0;

    if (!(avctx->flags2 & AV_CODEC_FLAG2_CHUNKS)) {
        h->current_slice = 0;
        if (!h->first_field) {
            h->cur_pic_ptr = NULL;
            ff_h264_sei_uninit(&h->sei);
        }
    }

    if (h->nal_length_size == 4) {
        if (buf_size > 8 && AV_RB32(buf) == 1 && AV_RB32(buf+5) > (unsigned)buf_size) {
            h->is_avc = 0;
        }else if(buf_size > 3 && AV_RB32(buf) > 1 && AV_RB32(buf) <= (unsigned)buf_size)
            h->is_avc = 1;
    }

    ret = ff_h2645_packet_split(&h->pkt, buf, buf_size, avctx, h->is_avc, h->nal_length_size,
                                avctx->codec_id, avctx->flags2 & AV_CODEC_FLAG2_FAST, 0);
    if (ret < 0) {
        av_log(avctx, AV_LOG_ERROR,
               "Error splitting the input into NAL units.\n");
        return ret;
    }

    if (avctx->active_thread_type & FF_THREAD_FRAME)
        nals_needed = get_last_needed_nal(h);
    if (nals_needed < 0)
        return nals_needed;

    for (i = 0; i < h->pkt.nb_nals; i++) {
        H2645NAL *nal = &h->pkt.nals[i];
        int max_slice_ctx, err;

        if (avctx->skip_frame >= AVDISCARD_NONREF &&
            nal->ref_idc == 0 && nal->type != H264_NAL_SEI)
            continue;

        // FIXME these should stop being context-global variables
        h->nal_ref_idc   = nal->ref_idc;
        h->nal_unit_type = nal->type;

        err = 0;
        switch (nal->type) {
        case H264_NAL_IDR_SLICE:
            if ((nal->data[1] & 0xFC) == 0x98) {
                av_log(h->avctx, AV_LOG_ERROR, "Invalid inter IDR frame\n");
                h->next_outputed_poc = INT_MIN;
                ret = -1;
                goto end;
            }
            if(!idr_cleared) {
                idr(h); // FIXME ensure we don't lose some frames if there is reordering
            }
            idr_cleared = 1;
            h->has_recovery_point = 1;
        case H264_NAL_SLICE:
            h->has_slice = 1;

            if ((err = ff_h264_queue_decode_slice(h, nal))) {
                H264SliceContext *sl = h->slice_ctx + h->nb_slice_ctx_queued;
                sl->ref_count[0] = sl->ref_count[1] = 0;
                break;
            }

            if (h->current_slice == 1) {
                if (avctx->active_thread_type & FF_THREAD_FRAME &&
                    i >= nals_needed && !h->setup_finished && h->cur_pic_ptr) {
                    ff_thread_finish_setup(avctx);
                    h->setup_finished = 1;
                }

                if (h->avctx->hwaccel &&
                    (ret = h->avctx->hwaccel->start_frame(h->avctx, buf, buf_size)) < 0)
                    goto end;
            }

            max_slice_ctx = avctx->hwaccel ? 1 : h->nb_slice_ctx;
            if (h->nb_slice_ctx_queued == max_slice_ctx) {
                if (h->avctx->hwaccel) {
                    ret = avctx->hwaccel->decode_slice(avctx, nal->raw_data, nal->raw_size);
                    h->nb_slice_ctx_queued = 0;
                } else
                    ret = ff_h264_execute_decode_slices(h);
                if (ret < 0 && (h->avctx->err_recognition & AV_EF_EXPLODE))
                    goto end;
            }
            break;
        case H264_NAL_DPA:
        case H264_NAL_DPB:
        case H264_NAL_DPC:
            avpriv_request_sample(avctx, "data partitioning");
            break;
        case H264_NAL_SEI:
            ret = ff_h264_sei_decode(&h->sei, &nal->gb, &h->ps, avctx);
            h->has_recovery_point = h->has_recovery_point || h->sei.recovery_point.recovery_frame_cnt != -1;
            if (avctx->debug & FF_DEBUG_GREEN_MD)
                debug_green_metadata(&h->sei.green_metadata, h->avctx);
            if (ret < 0 && (h->avctx->err_recognition & AV_EF_EXPLODE))
                goto end;
            break;
        case H264_NAL_SPS: {
            GetBitContext tmp_gb = nal->gb;
            if (avctx->hwaccel && avctx->hwaccel->decode_params) {
                ret = avctx->hwaccel->decode_params(avctx,
                                                    nal->type,
                                                    nal->raw_data,
                                                    nal->raw_size);
                if (ret < 0)
                    goto end;
            }
            if (ff_h264_decode_seq_parameter_set(&tmp_gb, avctx, &h->ps, 0) >= 0)
                break;
            av_log(h->avctx, AV_LOG_DEBUG,
                   "SPS decoding failure, trying again with the complete NAL\n");
            init_get_bits8(&tmp_gb, nal->raw_data + 1, nal->raw_size - 1);
            if (ff_h264_decode_seq_parameter_set(&tmp_gb, avctx, &h->ps, 0) >= 0)
                break;
            ff_h264_decode_seq_parameter_set(&nal->gb, avctx, &h->ps, 1);
            break;
        }
        case H264_NAL_PPS:
            if (avctx->hwaccel && avctx->hwaccel->decode_params) {
                ret = avctx->hwaccel->decode_params(avctx,
                                                    nal->type,
                                                    nal->raw_data,
                                                    nal->raw_size);
                if (ret < 0)
                    goto end;
            }
            ret = ff_h264_decode_picture_parameter_set(&nal->gb, avctx, &h->ps,
                                                       nal->size_bits);
            if (ret < 0 && (h->avctx->err_recognition & AV_EF_EXPLODE))
                goto end;
            break;
        case H264_NAL_AUD:
        case H264_NAL_END_SEQUENCE:
        case H264_NAL_END_STREAM:
        case H264_NAL_FILLER_DATA:
        case H264_NAL_SPS_EXT:
        case H264_NAL_AUXILIARY_SLICE:
            break;
        default:
            av_log(avctx, AV_LOG_DEBUG, "Unknown NAL code: %d (%d bits)\n",
                   nal->type, nal->size_bits);
        }

        if (err < 0) {
            av_log(h->avctx, AV_LOG_ERROR, "decode_slice_header error\n");
        }
    }

    ret = ff_h264_execute_decode_slices(h);
    if (ret < 0 && (h->avctx->err_recognition & AV_EF_EXPLODE))
        goto end;

    // set decode_error_flags to allow users to detect concealed decoding errors
    if ((ret < 0 || h->slice_ctx->er.error_occurred) && h->cur_pic_ptr) {
        h->cur_pic_ptr->f->decode_error_flags |= FF_DECODE_ERROR_DECODE_SLICES;
    }

    ret = 0;
end:

#if CONFIG_ERROR_RESILIENCE
    /*
     * FIXME: Error handling code does not seem to support interlaced
     * when slices span multiple rows
     * The ff_er_add_slice calls don't work right for bottom
     * fields; they cause massive erroneous error concealing
     * Error marking covers both fields (top and bottom).
     * This causes a mismatched s->error_count
     * and a bad error table. Further, the error count goes to
     * INT_MAX when called for bottom field, because mb_y is
     * past end by one (callers fault) and resync_mb_y != 0
     * causes problems for the first MB line, too.
     */
    if (!FIELD_PICTURE(h) && h->current_slice &&
        h->ps.sps == (const SPS*)h->ps.sps_list[h->ps.pps->sps_id]->data &&
        h->enable_er) {

        H264SliceContext *sl = h->slice_ctx;
        int use_last_pic = h->last_pic_for_ec.f->buf[0] && !sl->ref_count[0];

        ff_h264_set_erpic(&sl->er.cur_pic, h->cur_pic_ptr);

        if (use_last_pic) {
            ff_h264_set_erpic(&sl->er.last_pic, &h->last_pic_for_ec);
            sl->ref_list[0][0].parent = &h->last_pic_for_ec;
            memcpy(sl->ref_list[0][0].data, h->last_pic_for_ec.f->data, sizeof(sl->ref_list[0][0].data));
            memcpy(sl->ref_list[0][0].linesize, h->last_pic_for_ec.f->linesize, sizeof(sl->ref_list[0][0].linesize));
            sl->ref_list[0][0].reference = h->last_pic_for_ec.reference;
        } else if (sl->ref_count[0]) {
            ff_h264_set_erpic(&sl->er.last_pic, sl->ref_list[0][0].parent);
        } else
            ff_h264_set_erpic(&sl->er.last_pic, NULL);

        if (sl->ref_count[1])
            ff_h264_set_erpic(&sl->er.next_pic, sl->ref_list[1][0].parent);

        sl->er.ref_count = sl->ref_count[0];

        ff_er_frame_end(&sl->er);
        if (use_last_pic)
            memset(&sl->ref_list[0][0], 0, sizeof(sl->ref_list[0][0]));
    }
#endif /* CONFIG_ERROR_RESILIENCE */
    /* clean up */
    if (h->cur_pic_ptr && !h->droppable && h->has_slice) {
        ff_thread_report_progress(&h->cur_pic_ptr->tf, INT_MAX,
                                  h->picture_structure == PICT_BOTTOM_FIELD);
    }

    return (ret < 0) ? ret : buf_size;
}