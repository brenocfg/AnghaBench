#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_22__ ;
typedef  struct TYPE_25__   TYPE_20__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_31__ {int code_word; int bits; int /*<<< orphan*/  high; scalar_t__ buffer; } ;
struct TYPE_27__ {int value; int bit_count; int /*<<< orphan*/  range; scalar_t__ input; } ;
struct TYPE_25__ {void* update; void* enabled; scalar_t__ update_map; } ;
struct TYPE_24__ {void* sharpness; void* level; void* simple; } ;
struct TYPE_28__ {int /*<<< orphan*/  put_vp8_bilinear_pixels_tab; int /*<<< orphan*/  put_vp8_epel_pixels_tab; } ;
struct TYPE_30__ {int keyframe; int profile; int invisible; int header_partition_size; int mb_width; int mb_height; int update_last; TYPE_6__ c; TYPE_2__ coder_state_at_header_end; TYPE_4__* prob; void* mbskip_enabled; void* update_probabilities; void** sign_bias; TYPE_22__* avctx; int /*<<< orphan*/  macroblocks_base; TYPE_20__ lf_delta; TYPE_1__ filter; TYPE_20__ segmentation; void* fullrange; void* colorspace; int /*<<< orphan*/  update_altref; int /*<<< orphan*/  update_golden; TYPE_3__ vp8dsp; int /*<<< orphan*/  put_pixels_tab; } ;
typedef  TYPE_5__ VP8Context ;
typedef  TYPE_6__ VP56RangeCoder ;
struct TYPE_29__ {void* golden; void* last; void* intra; void* mbskip; int /*<<< orphan*/  mvc; int /*<<< orphan*/  pred8x8c; int /*<<< orphan*/  pred16x16; } ;
struct TYPE_26__ {int width; int height; } ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_RL16 (int const*) ; 
 int AV_RL24 (int const*) ; 
 int /*<<< orphan*/  VP56_FRAME_CURRENT ; 
 size_t VP56_FRAME_GOLDEN ; 
 size_t VP56_FRAME_GOLDEN2 ; 
 int /*<<< orphan*/  VP8_MVC_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_22__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_22__*,char*) ; 
 int ff_vp56_init_range_decoder (TYPE_6__*,int const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_20__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_segment_info (TYPE_5__*) ; 
 scalar_t__ setup_partitions (TYPE_5__*,int const*,int) ; 
 int /*<<< orphan*/  update_lf_deltas (TYPE_5__*) ; 
 int /*<<< orphan*/  update_refs (TYPE_5__*) ; 
 int vp56_rac_renorm (TYPE_6__*) ; 
 int /*<<< orphan*/  vp78_reset_probability_tables (TYPE_5__*) ; 
 int /*<<< orphan*/  vp78_update_pred16x16_pred8x8_mvc_probabilities (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vp78_update_probability_tables (TYPE_5__*) ; 
 int /*<<< orphan*/  vp8_get_quants (TYPE_5__*) ; 
 int /*<<< orphan*/  vp8_mv_default_prob ; 
 int /*<<< orphan*/  vp8_pred16x16_prob_inter ; 
 int /*<<< orphan*/  vp8_pred8x8c_prob_inter ; 
 void* vp8_rac_get (TYPE_6__*) ; 
 void* vp8_rac_get_uint (TYPE_6__*,int) ; 
 int vp8_update_dimensions (TYPE_5__*,int,int) ; 

__attribute__((used)) static int vp8_decode_frame_header(VP8Context *s, const uint8_t *buf, int buf_size)
{
    VP56RangeCoder *c = &s->c;
    int header_size, hscale, vscale, ret;
    int width  = s->avctx->width;
    int height = s->avctx->height;

    if (buf_size < 3) {
        av_log(s->avctx, AV_LOG_ERROR, "Insufficent data (%d) for header\n", buf_size);
        return AVERROR_INVALIDDATA;
    }

    s->keyframe  = !(buf[0] & 1);
    s->profile   =  (buf[0]>>1) & 7;
    s->invisible = !(buf[0] & 0x10);
    header_size  = AV_RL24(buf) >> 5;
    buf      += 3;
    buf_size -= 3;

    s->header_partition_size = header_size;

    if (s->profile > 3)
        av_log(s->avctx, AV_LOG_WARNING, "Unknown profile %d\n", s->profile);

    if (!s->profile)
        memcpy(s->put_pixels_tab, s->vp8dsp.put_vp8_epel_pixels_tab,
               sizeof(s->put_pixels_tab));
    else    // profile 1-3 use bilinear, 4+ aren't defined so whatever
        memcpy(s->put_pixels_tab, s->vp8dsp.put_vp8_bilinear_pixels_tab,
               sizeof(s->put_pixels_tab));

    if (header_size > buf_size - 7 * s->keyframe) {
        av_log(s->avctx, AV_LOG_ERROR, "Header size larger than data provided\n");
        return AVERROR_INVALIDDATA;
    }

    if (s->keyframe) {
        if (AV_RL24(buf) != 0x2a019d) {
            av_log(s->avctx, AV_LOG_ERROR,
                   "Invalid start code 0x%x\n", AV_RL24(buf));
            return AVERROR_INVALIDDATA;
        }
        width     = AV_RL16(buf + 3) & 0x3fff;
        height    = AV_RL16(buf + 5) & 0x3fff;
        hscale    = buf[4] >> 6;
        vscale    = buf[6] >> 6;
        buf      += 7;
        buf_size -= 7;

        if (hscale || vscale)
            avpriv_request_sample(s->avctx, "Upscaling");

        s->update_golden = s->update_altref = VP56_FRAME_CURRENT;
        vp78_reset_probability_tables(s);
        memcpy(s->prob->pred16x16, vp8_pred16x16_prob_inter,
               sizeof(s->prob->pred16x16));
        memcpy(s->prob->pred8x8c, vp8_pred8x8c_prob_inter,
               sizeof(s->prob->pred8x8c));
        memcpy(s->prob->mvc, vp8_mv_default_prob,
               sizeof(s->prob->mvc));
        memset(&s->segmentation, 0, sizeof(s->segmentation));
        memset(&s->lf_delta, 0, sizeof(s->lf_delta));
    }

    ret = ff_vp56_init_range_decoder(c, buf, header_size);
    if (ret < 0)
        return ret;
    buf      += header_size;
    buf_size -= header_size;

    if (s->keyframe) {
        s->colorspace = vp8_rac_get(c);
        if (s->colorspace)
            av_log(s->avctx, AV_LOG_WARNING, "Unspecified colorspace\n");
        s->fullrange = vp8_rac_get(c);
    }

    if ((s->segmentation.enabled = vp8_rac_get(c)))
        parse_segment_info(s);
    else
        s->segmentation.update_map = 0; // FIXME: move this to some init function?

    s->filter.simple    = vp8_rac_get(c);
    s->filter.level     = vp8_rac_get_uint(c, 6);
    s->filter.sharpness = vp8_rac_get_uint(c, 3);

    if ((s->lf_delta.enabled = vp8_rac_get(c))) {
        s->lf_delta.update = vp8_rac_get(c);
        if (s->lf_delta.update)
            update_lf_deltas(s);
    }

    if (setup_partitions(s, buf, buf_size)) {
        av_log(s->avctx, AV_LOG_ERROR, "Invalid partitions\n");
        return AVERROR_INVALIDDATA;
    }

    if (!s->macroblocks_base || /* first frame */
        width != s->avctx->width || height != s->avctx->height ||
        (width+15)/16 != s->mb_width || (height+15)/16 != s->mb_height)
        if ((ret = vp8_update_dimensions(s, width, height)) < 0)
            return ret;

    vp8_get_quants(s);

    if (!s->keyframe) {
        update_refs(s);
        s->sign_bias[VP56_FRAME_GOLDEN]               = vp8_rac_get(c);
        s->sign_bias[VP56_FRAME_GOLDEN2 /* altref */] = vp8_rac_get(c);
    }

    // if we aren't saving this frame's probabilities for future frames,
    // make a copy of the current probabilities
    if (!(s->update_probabilities = vp8_rac_get(c)))
        s->prob[1] = s->prob[0];

    s->update_last = s->keyframe || vp8_rac_get(c);

    vp78_update_probability_tables(s);

    if ((s->mbskip_enabled = vp8_rac_get(c)))
        s->prob->mbskip = vp8_rac_get_uint(c, 8);

    if (!s->keyframe) {
        s->prob->intra  = vp8_rac_get_uint(c, 8);
        s->prob->last   = vp8_rac_get_uint(c, 8);
        s->prob->golden = vp8_rac_get_uint(c, 8);
        vp78_update_pred16x16_pred8x8_mvc_probabilities(s, VP8_MVC_SIZE);
    }

    // Record the entropy coder state here so that hwaccels can use it.
    s->c.code_word = vp56_rac_renorm(&s->c);
    s->coder_state_at_header_end.input     = s->c.buffer - (-s->c.bits / 8);
    s->coder_state_at_header_end.range     = s->c.high;
    s->coder_state_at_header_end.value     = s->c.code_word >> 16;
    s->coder_state_at_header_end.bit_count = -s->c.bits % 8;

    return 0;
}