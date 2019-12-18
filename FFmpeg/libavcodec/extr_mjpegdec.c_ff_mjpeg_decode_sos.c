#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_22__ {scalar_t__ codec_tag; scalar_t__ pix_fmt; int debug; TYPE_2__* hwaccel; } ;
struct TYPE_21__ {scalar_t__ width; scalar_t__ height; scalar_t__ format; } ;
struct TYPE_20__ {int nb_components; int* component_id; int* nb_blocks; int* h_count; int* v_count; int* h_scount; int* v_scount; int* comp_index; int* dc_index; int* ac_index; int mb_width; int const width; int const h_max; int mb_height; int const height; int const v_max; int bits; int mjpb_skiptosod; int* last_dc; int raw_scan_buffer_size; int bottom_field; TYPE_6__* avctx; int /*<<< orphan*/  gb; scalar_t__ interlaced; TYPE_3__* picture; TYPE_3__* picture_ptr; scalar_t__ progressive; scalar_t__ bayer; scalar_t__ rgb; scalar_t__ ls; scalar_t__ lossless; scalar_t__ raw_scan_buffer; scalar_t__ rct; scalar_t__ pegasus_rct; TYPE_1__** vlcs; int /*<<< orphan*/ * quant_index; int /*<<< orphan*/ * quant_sindex; int /*<<< orphan*/  got_picture; } ;
struct TYPE_19__ {scalar_t__ width; scalar_t__ height; scalar_t__ format; } ;
struct TYPE_18__ {int (* decode_slice ) (TYPE_6__*,scalar_t__,int) ;} ;
struct TYPE_17__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_4__ MJpegDecodeContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_5__ AVFrame ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_PIX_FMT_GBR24P ; 
 scalar_t__ AV_RL32 (char*) ; 
 scalar_t__ CONFIG_JPEGLS_DECODER ; 
 int FF_DEBUG_PICT_INFO ; 
 int MAX_COMPONENTS ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_6__*,char*,int) ; 
 int /*<<< orphan*/  emms_c () ; 
 int ff_jpegls_decode_picture (TYPE_4__*,int,int,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int ljpeg_decode_rgb_scan (TYPE_4__*,int,int,int) ; 
 int ljpeg_decode_yuv_scan (TYPE_4__*,int,int,int) ; 
 int mjpeg_decode_scan (TYPE_4__*,int,int,int,int /*<<< orphan*/  const*,int,TYPE_5__ const*) ; 
 int mjpeg_decode_scan_progressive_ac (TYPE_4__*,int,int,int,int) ; 
 int show_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int stub1 (TYPE_6__*,scalar_t__,int) ; 

int ff_mjpeg_decode_sos(MJpegDecodeContext *s, const uint8_t *mb_bitmask,
                        int mb_bitmask_size, const AVFrame *reference)
{
    int len, nb_components, i, h, v, predictor, point_transform;
    int index, id, ret;
    const int block_size = s->lossless ? 1 : 8;
    int ilv, prev_shift;

    if (!s->got_picture) {
        av_log(s->avctx, AV_LOG_WARNING,
                "Can not process SOS before SOF, skipping\n");
        return -1;
    }

    if (reference) {
        if (reference->width  != s->picture_ptr->width  ||
            reference->height != s->picture_ptr->height ||
            reference->format != s->picture_ptr->format) {
            av_log(s->avctx, AV_LOG_ERROR, "Reference mismatching\n");
            return AVERROR_INVALIDDATA;
        }
    }

    /* XXX: verify len field validity */
    len = get_bits(&s->gb, 16);
    nb_components = get_bits(&s->gb, 8);
    if (nb_components == 0 || nb_components > MAX_COMPONENTS) {
        avpriv_report_missing_feature(s->avctx,
                                      "decode_sos: nb_components (%d)",
                                      nb_components);
        return AVERROR_PATCHWELCOME;
    }
    if (len != 6 + 2 * nb_components) {
        av_log(s->avctx, AV_LOG_ERROR, "decode_sos: invalid len (%d)\n", len);
        return AVERROR_INVALIDDATA;
    }
    for (i = 0; i < nb_components; i++) {
        id = get_bits(&s->gb, 8) - 1;
        av_log(s->avctx, AV_LOG_DEBUG, "component: %d\n", id);
        /* find component index */
        for (index = 0; index < s->nb_components; index++)
            if (id == s->component_id[index])
                break;
        if (index == s->nb_components) {
            av_log(s->avctx, AV_LOG_ERROR,
                   "decode_sos: index(%d) out of components\n", index);
            return AVERROR_INVALIDDATA;
        }
        /* Metasoft MJPEG codec has Cb and Cr swapped */
        if (s->avctx->codec_tag == MKTAG('M', 'T', 'S', 'J')
            && nb_components == 3 && s->nb_components == 3 && i)
            index = 3 - i;

        s->quant_sindex[i] = s->quant_index[index];
        s->nb_blocks[i] = s->h_count[index] * s->v_count[index];
        s->h_scount[i]  = s->h_count[index];
        s->v_scount[i]  = s->v_count[index];

        if((nb_components == 1 || nb_components == 3) && s->nb_components == 3 && s->avctx->pix_fmt == AV_PIX_FMT_GBR24P)
            index = (index+2)%3;

        s->comp_index[i] = index;

        s->dc_index[i] = get_bits(&s->gb, 4);
        s->ac_index[i] = get_bits(&s->gb, 4);

        if (s->dc_index[i] <  0 || s->ac_index[i] < 0 ||
            s->dc_index[i] >= 4 || s->ac_index[i] >= 4)
            goto out_of_range;
        if (!s->vlcs[0][s->dc_index[i]].table || !(s->progressive ? s->vlcs[2][s->ac_index[0]].table : s->vlcs[1][s->ac_index[i]].table))
            goto out_of_range;
    }

    predictor = get_bits(&s->gb, 8);       /* JPEG Ss / lossless JPEG predictor /JPEG-LS NEAR */
    ilv = get_bits(&s->gb, 8);             /* JPEG Se / JPEG-LS ILV */
    if(s->avctx->codec_tag != AV_RL32("CJPG")){
        prev_shift      = get_bits(&s->gb, 4); /* Ah */
        point_transform = get_bits(&s->gb, 4); /* Al */
    }else
        prev_shift = point_transform = 0;

    if (nb_components > 1) {
        /* interleaved stream */
        s->mb_width  = (s->width  + s->h_max * block_size - 1) / (s->h_max * block_size);
        s->mb_height = (s->height + s->v_max * block_size - 1) / (s->v_max * block_size);
    } else if (!s->ls) { /* skip this for JPEG-LS */
        h = s->h_max / s->h_scount[0];
        v = s->v_max / s->v_scount[0];
        s->mb_width     = (s->width  + h * block_size - 1) / (h * block_size);
        s->mb_height    = (s->height + v * block_size - 1) / (v * block_size);
        s->nb_blocks[0] = 1;
        s->h_scount[0]  = 1;
        s->v_scount[0]  = 1;
    }

    if (s->avctx->debug & FF_DEBUG_PICT_INFO)
        av_log(s->avctx, AV_LOG_DEBUG, "%s %s p:%d >>:%d ilv:%d bits:%d skip:%d %s comp:%d\n",
               s->lossless ? "lossless" : "sequential DCT", s->rgb ? "RGB" : "",
               predictor, point_transform, ilv, s->bits, s->mjpb_skiptosod,
               s->pegasus_rct ? "PRCT" : (s->rct ? "RCT" : ""), nb_components);


    /* mjpeg-b can have padding bytes between sos and image data, skip them */
    for (i = s->mjpb_skiptosod; i > 0; i--)
        skip_bits(&s->gb, 8);

next_field:
    for (i = 0; i < nb_components; i++)
        s->last_dc[i] = (4 << s->bits);

    if (s->avctx->hwaccel) {
        int bytes_to_start = get_bits_count(&s->gb) / 8;
        av_assert0(bytes_to_start >= 0 &&
                   s->raw_scan_buffer_size >= bytes_to_start);

        ret = s->avctx->hwaccel->decode_slice(s->avctx,
                                              s->raw_scan_buffer      + bytes_to_start,
                                              s->raw_scan_buffer_size - bytes_to_start);
        if (ret < 0)
            return ret;

    } else if (s->lossless) {
        av_assert0(s->picture_ptr == s->picture);
        if (CONFIG_JPEGLS_DECODER && s->ls) {
//            for () {
//            reset_ls_coding_parameters(s, 0);

            if ((ret = ff_jpegls_decode_picture(s, predictor,
                                                point_transform, ilv)) < 0)
                return ret;
        } else {
            if (s->rgb || s->bayer) {
                if ((ret = ljpeg_decode_rgb_scan(s, nb_components, predictor, point_transform)) < 0)
                    return ret;
            } else {
                if ((ret = ljpeg_decode_yuv_scan(s, predictor,
                                                 point_transform,
                                                 nb_components)) < 0)
                    return ret;
            }
        }
    } else {
        if (s->progressive && predictor) {
            av_assert0(s->picture_ptr == s->picture);
            if ((ret = mjpeg_decode_scan_progressive_ac(s, predictor,
                                                        ilv, prev_shift,
                                                        point_transform)) < 0)
                return ret;
        } else {
            if ((ret = mjpeg_decode_scan(s, nb_components,
                                         prev_shift, point_transform,
                                         mb_bitmask, mb_bitmask_size, reference)) < 0)
                return ret;
        }
    }

    if (s->interlaced &&
        get_bits_left(&s->gb) > 32 &&
        show_bits(&s->gb, 8) == 0xFF) {
        GetBitContext bak = s->gb;
        align_get_bits(&bak);
        if (show_bits(&bak, 16) == 0xFFD1) {
            av_log(s->avctx, AV_LOG_DEBUG, "AVRn interlaced picture marker found\n");
            s->gb = bak;
            skip_bits(&s->gb, 16);
            s->bottom_field ^= 1;

            goto next_field;
        }
    }

    emms_c();
    return 0;
 out_of_range:
    av_log(s->avctx, AV_LOG_ERROR, "decode_sos: ac/dc index out of range\n");
    return AVERROR_INVALIDDATA;
}