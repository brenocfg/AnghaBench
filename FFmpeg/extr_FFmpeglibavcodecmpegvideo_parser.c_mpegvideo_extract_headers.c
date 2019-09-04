#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_10__ {int num; int den; } ;
struct MpvParseContext {int width; int height; int progressive_sequence; TYPE_6__ frame_rate; } ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_9__ {scalar_t__ codec_id; int ticks_per_frame; int has_b_frames; long long rc_max_rate; long long bit_rate; TYPE_6__ framerate; int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {int repeat_pict; int pict_type; int format; int width; int height; void* coded_height; void* coded_width; int /*<<< orphan*/  field_order; struct MpvParseContext* priv_data; } ;
typedef  TYPE_1__ AVCodecParserContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_MPEG1VIDEO ; 
 scalar_t__ AV_CODEC_ID_MPEG2VIDEO ; 
 int /*<<< orphan*/  AV_FIELD_BB ; 
 int /*<<< orphan*/  AV_FIELD_PROGRESSIVE ; 
 int /*<<< orphan*/  AV_FIELD_TT ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PIX_FMT_NONE ; 
 int AV_PIX_FMT_YUV420P ; 
 int AV_PIX_FMT_YUV422P ; 
 int AV_PIX_FMT_YUV444P ; 
#define  EXT_START_CODE 130 
 void* FFALIGN (int,int) ; 
#define  PICTURE_START_CODE 129 
#define  SEQ_START_CODE 128 
 int SLICE_MAX_START_CODE ; 
 int SLICE_MIN_START_CODE ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int* avpriv_find_start_code (int const*,int const*,int*) ; 
 TYPE_6__* ff_mpeg12_frame_rate_tab ; 
 int ff_set_dimensions (TYPE_2__*,int,int) ; 

__attribute__((used)) static void mpegvideo_extract_headers(AVCodecParserContext *s,
                                      AVCodecContext *avctx,
                                      const uint8_t *buf, int buf_size)
{
    struct MpvParseContext *pc = s->priv_data;
    const uint8_t *buf_end = buf + buf_size;
    uint32_t start_code;
    int frame_rate_index, ext_type, bytes_left;
    int frame_rate_ext_n, frame_rate_ext_d;
    int top_field_first, repeat_first_field, progressive_frame;
    int horiz_size_ext, vert_size_ext, bit_rate_ext;
    int did_set_size=0;
    int set_dim_ret = 0;
    int bit_rate = 0;
    int vbv_delay = 0;
    int chroma_format;
    enum AVPixelFormat pix_fmt = AV_PIX_FMT_NONE;
//FIXME replace the crap with get_bits()
    s->repeat_pict = 0;

    while (buf < buf_end) {
        start_code= -1;
        buf= avpriv_find_start_code(buf, buf_end, &start_code);
        bytes_left = buf_end - buf;
        switch(start_code) {
        case PICTURE_START_CODE:
            if (bytes_left >= 2) {
                s->pict_type = (buf[1] >> 3) & 7;
                if (bytes_left >= 4)
                    vbv_delay = ((buf[1] & 0x07) << 13) | (buf[2] << 5) | (buf[3] >> 3);
            }
            break;
        case SEQ_START_CODE:
            if (bytes_left >= 7) {
                pc->width  = (buf[0] << 4) | (buf[1] >> 4);
                pc->height = ((buf[1] & 0x0f) << 8) | buf[2];
                if(!avctx->width || !avctx->height || !avctx->coded_width || !avctx->coded_height){
                    set_dim_ret = ff_set_dimensions(avctx, pc->width, pc->height);
                    did_set_size=1;
                }
                pix_fmt = AV_PIX_FMT_YUV420P;
                frame_rate_index = buf[3] & 0xf;
                pc->frame_rate = avctx->framerate = ff_mpeg12_frame_rate_tab[frame_rate_index];
                bit_rate = (buf[4]<<10) | (buf[5]<<2) | (buf[6]>>6);
                avctx->codec_id = AV_CODEC_ID_MPEG1VIDEO;
                avctx->ticks_per_frame = 1;
            }
            break;
        case EXT_START_CODE:
            if (bytes_left >= 1) {
                ext_type = (buf[0] >> 4);
                switch(ext_type) {
                case 0x1: /* sequence extension */
                    if (bytes_left >= 6) {
                        horiz_size_ext = ((buf[1] & 1) << 1) | (buf[2] >> 7);
                        vert_size_ext = (buf[2] >> 5) & 3;
                        bit_rate_ext = ((buf[2] & 0x1F)<<7) | (buf[3]>>1);
                        frame_rate_ext_n = (buf[5] >> 5) & 3;
                        frame_rate_ext_d = (buf[5] & 0x1f);
                        pc->progressive_sequence = buf[1] & (1 << 3);
                        avctx->has_b_frames= !(buf[5] >> 7);

                        chroma_format = (buf[1] >> 1) & 3;
                        switch (chroma_format) {
                        case 1: pix_fmt = AV_PIX_FMT_YUV420P; break;
                        case 2: pix_fmt = AV_PIX_FMT_YUV422P; break;
                        case 3: pix_fmt = AV_PIX_FMT_YUV444P; break;
                        }

                        pc->width  = (pc->width & 0xFFF) | (horiz_size_ext << 12);
                        pc->height = (pc->height& 0xFFF) | ( vert_size_ext << 12);
                        bit_rate = (bit_rate&0x3FFFF) | (bit_rate_ext << 18);
                        if(did_set_size)
                            set_dim_ret = ff_set_dimensions(avctx, pc->width, pc->height);
                        avctx->framerate.num = pc->frame_rate.num * (frame_rate_ext_n + 1);
                        avctx->framerate.den = pc->frame_rate.den * (frame_rate_ext_d + 1);
                        avctx->codec_id = AV_CODEC_ID_MPEG2VIDEO;
                        avctx->ticks_per_frame = 2;
                    }
                    break;
                case 0x8: /* picture coding extension */
                    if (bytes_left >= 5) {
                        top_field_first = buf[3] & (1 << 7);
                        repeat_first_field = buf[3] & (1 << 1);
                        progressive_frame = buf[4] & (1 << 7);

                        /* check if we must repeat the frame */
                        s->repeat_pict = 1;
                        if (repeat_first_field) {
                            if (pc->progressive_sequence) {
                                if (top_field_first)
                                    s->repeat_pict = 5;
                                else
                                    s->repeat_pict = 3;
                            } else if (progressive_frame) {
                                s->repeat_pict = 2;
                            }
                        }

                        if (!pc->progressive_sequence && !progressive_frame) {
                            if (top_field_first)
                                s->field_order = AV_FIELD_TT;
                            else
                                s->field_order = AV_FIELD_BB;
                        } else
                            s->field_order = AV_FIELD_PROGRESSIVE;
                    }
                    break;
                }
            }
            break;
        case -1:
            goto the_end;
        default:
            /* we stop parsing when we encounter a slice. It ensures
               that this function takes a negligible amount of time */
            if (start_code >= SLICE_MIN_START_CODE &&
                start_code <= SLICE_MAX_START_CODE)
                goto the_end;
            break;
        }
    }
 the_end: ;
    if (set_dim_ret < 0)
        av_log(avctx, AV_LOG_ERROR, "Failed to set dimensions\n");

    if (avctx->codec_id == AV_CODEC_ID_MPEG2VIDEO && bit_rate) {
        avctx->rc_max_rate = 400LL*bit_rate;
    }
    if (bit_rate &&
        ((avctx->codec_id == AV_CODEC_ID_MPEG1VIDEO && bit_rate != 0x3FFFF) || vbv_delay != 0xFFFF)) {
        avctx->bit_rate = 400LL*bit_rate;
    }

    if (pix_fmt != AV_PIX_FMT_NONE) {
        s->format = pix_fmt;
        s->width  = pc->width;
        s->height = pc->height;
        s->coded_width  = FFALIGN(pc->width,  16);
        s->coded_height = FFALIGN(pc->height, 16);
    }

#if FF_API_AVCTX_TIMEBASE
    if (avctx->framerate.num)
        avctx->time_base = av_inv_q(av_mul_q(avctx->framerate, (AVRational){avctx->ticks_per_frame, 1}));
#endif
}