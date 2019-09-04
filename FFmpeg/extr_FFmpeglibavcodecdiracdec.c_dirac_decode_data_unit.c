#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_30__ {int key_frame; int pict_type; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_29__ {long long max_pixels; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  framerate; int /*<<< orphan*/  level; int /*<<< orphan*/  profile; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  color_primaries; int /*<<< orphan*/  color_trc; int /*<<< orphan*/  color_range; TYPE_5__* priv_data; } ;
struct TYPE_25__ {int minor; int /*<<< orphan*/  major; } ;
struct TYPE_28__ {int bit_depth; TYPE_3__ version; int /*<<< orphan*/  framerate; int /*<<< orphan*/  level; int /*<<< orphan*/  profile; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  color_primaries; int /*<<< orphan*/  color_trc; int /*<<< orphan*/  color_range; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  sample_aspect_ratio; scalar_t__ height; scalar_t__ width; } ;
struct TYPE_24__ {int minor; int /*<<< orphan*/  major; } ;
struct TYPE_27__ {int seen_sequence_header; int bit_depth; int pshift; int old_delta_quant; unsigned int num_refs; int is_arith; int low_delay; int core_syntax; int ld_picture; int hq_picture; int dc_prediction; TYPE_1__* plane; TYPE_4__* current_picture; TYPE_2__ version; TYPE_4__* all_frames; int /*<<< orphan*/  chroma_y_shift; int /*<<< orphan*/  chroma_x_shift; TYPE_6__ seq; int /*<<< orphan*/  gb; } ;
struct TYPE_26__ {int reference; TYPE_9__* avframe; } ;
struct TYPE_23__ {int /*<<< orphan*/  stride; } ;
typedef  TYPE_4__ DiracFrame ;
typedef  TYPE_5__ DiracContext ;
typedef  TYPE_6__ AVDiracSeqHeader ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 long long CALC_PADDING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DATA_UNIT_HEADER_SIZE ; 
 int DIRAC_PCODE_AUX ; 
 int DIRAC_PCODE_END_SEQ ; 
 int DIRAC_PCODE_SEQ_HEADER ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  FFABS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FFMAX3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_DWT_LEVELS ; 
 int MAX_FRAMES ; 
 scalar_t__ alloc_buffers (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int alloc_sequence_buffers (TYPE_5__*) ; 
 int av_dirac_parse_sequence_header (TYPE_6__**,int const*,int,TYPE_7__*) ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_9__*) ; 
 int /*<<< orphan*/  av_freep (TYPE_6__**) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 int av_pix_fmt_get_chroma_sub_sample (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dirac_decode_frame_internal (TYPE_5__*) ; 
 int dirac_decode_picture_header (TYPE_5__*) ; 
 int ff_set_dimensions (TYPE_7__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ff_set_sar (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_sequence_buffers (TYPE_5__*) ; 
 int get_buffer_with_edge (TYPE_7__*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int const*,int) ; 
 int sscanf (int const*,char*,int*,int*,int*) ; 

__attribute__((used)) static int dirac_decode_data_unit(AVCodecContext *avctx, const uint8_t *buf, int size)
{
    DiracContext *s   = avctx->priv_data;
    DiracFrame *pic   = NULL;
    AVDiracSeqHeader *dsh;
    int ret, i;
    uint8_t parse_code;
    unsigned tmp;

    if (size < DATA_UNIT_HEADER_SIZE)
        return AVERROR_INVALIDDATA;

    parse_code = buf[4];

    init_get_bits(&s->gb, &buf[13], 8*(size - DATA_UNIT_HEADER_SIZE));

    if (parse_code == DIRAC_PCODE_SEQ_HEADER) {
        if (s->seen_sequence_header)
            return 0;

        /* [DIRAC_STD] 10. Sequence header */
        ret = av_dirac_parse_sequence_header(&dsh, buf + DATA_UNIT_HEADER_SIZE, size - DATA_UNIT_HEADER_SIZE, avctx);
        if (ret < 0) {
            av_log(avctx, AV_LOG_ERROR, "error parsing sequence header");
            return ret;
        }

        if (CALC_PADDING((int64_t)dsh->width, MAX_DWT_LEVELS) * CALC_PADDING((int64_t)dsh->height, MAX_DWT_LEVELS) * 5LL > avctx->max_pixels)
            ret = AVERROR(ERANGE);
        if (ret >= 0)
            ret = ff_set_dimensions(avctx, dsh->width, dsh->height);
        if (ret < 0) {
            av_freep(&dsh);
            return ret;
        }

        ff_set_sar(avctx, dsh->sample_aspect_ratio);
        avctx->pix_fmt         = dsh->pix_fmt;
        avctx->color_range     = dsh->color_range;
        avctx->color_trc       = dsh->color_trc;
        avctx->color_primaries = dsh->color_primaries;
        avctx->colorspace      = dsh->colorspace;
        avctx->profile         = dsh->profile;
        avctx->level           = dsh->level;
        avctx->framerate       = dsh->framerate;
        s->bit_depth           = dsh->bit_depth;
        s->version.major       = dsh->version.major;
        s->version.minor       = dsh->version.minor;
        s->seq                 = *dsh;
        av_freep(&dsh);

        s->pshift = s->bit_depth > 8;

        ret = av_pix_fmt_get_chroma_sub_sample(avctx->pix_fmt,
                                               &s->chroma_x_shift,
                                               &s->chroma_y_shift);
        if (ret < 0)
            return ret;

        ret = alloc_sequence_buffers(s);
        if (ret < 0)
            return ret;

        s->seen_sequence_header = 1;
    } else if (parse_code == DIRAC_PCODE_END_SEQ) { /* [DIRAC_STD] End of Sequence */
        free_sequence_buffers(s);
        s->seen_sequence_header = 0;
    } else if (parse_code == DIRAC_PCODE_AUX) {
        if (buf[13] == 1) {     /* encoder implementation/version */
            int ver[3];
            /* versions older than 1.0.8 don't store quant delta for
               subbands with only one codeblock */
            if (sscanf(buf+14, "Schroedinger %d.%d.%d", ver, ver+1, ver+2) == 3)
                if (ver[0] == 1 && ver[1] == 0 && ver[2] <= 7)
                    s->old_delta_quant = 1;
        }
    } else if (parse_code & 0x8) {  /* picture data unit */
        if (!s->seen_sequence_header) {
            av_log(avctx, AV_LOG_DEBUG, "Dropping frame without sequence header\n");
            return AVERROR_INVALIDDATA;
        }

        /* find an unused frame */
        for (i = 0; i < MAX_FRAMES; i++)
            if (s->all_frames[i].avframe->data[0] == NULL)
                pic = &s->all_frames[i];
        if (!pic) {
            av_log(avctx, AV_LOG_ERROR, "framelist full\n");
            return AVERROR_INVALIDDATA;
        }

        av_frame_unref(pic->avframe);

        /* [DIRAC_STD] Defined in 9.6.1 ... */
        tmp            =  parse_code & 0x03;                   /* [DIRAC_STD] num_refs()      */
        if (tmp > 2) {
            av_log(avctx, AV_LOG_ERROR, "num_refs of 3\n");
            return AVERROR_INVALIDDATA;
        }
        s->num_refs      = tmp;
        s->is_arith      = (parse_code & 0x48) == 0x08;          /* [DIRAC_STD] using_ac()            */
        s->low_delay     = (parse_code & 0x88) == 0x88;          /* [DIRAC_STD] is_low_delay()        */
        s->core_syntax   = (parse_code & 0x88) == 0x08;          /* [DIRAC_STD] is_core_syntax()      */
        s->ld_picture    = (parse_code & 0xF8) == 0xC8;          /* [DIRAC_STD] is_ld_picture()       */
        s->hq_picture    = (parse_code & 0xF8) == 0xE8;          /* [DIRAC_STD] is_hq_picture()       */
        s->dc_prediction = (parse_code & 0x28) == 0x08;          /* [DIRAC_STD] using_dc_prediction() */
        pic->reference   = (parse_code & 0x0C) == 0x0C;          /* [DIRAC_STD] is_reference()        */
        pic->avframe->key_frame = s->num_refs == 0;              /* [DIRAC_STD] is_intra()            */
        pic->avframe->pict_type = s->num_refs + 1;               /* Definition of AVPictureType in avutil.h */

        /* VC-2 Low Delay has a different parse code than the Dirac Low Delay */
        if (s->version.minor == 2 && parse_code == 0x88)
            s->ld_picture = 1;

        if (s->low_delay && !(s->ld_picture || s->hq_picture) ) {
            av_log(avctx, AV_LOG_ERROR, "Invalid low delay flag\n");
            return AVERROR_INVALIDDATA;
        }

        if ((ret = get_buffer_with_edge(avctx, pic->avframe, (parse_code & 0x0C) == 0x0C ? AV_GET_BUFFER_FLAG_REF : 0)) < 0)
            return ret;
        s->current_picture = pic;
        s->plane[0].stride = pic->avframe->linesize[0];
        s->plane[1].stride = pic->avframe->linesize[1];
        s->plane[2].stride = pic->avframe->linesize[2];

        if (alloc_buffers(s, FFMAX3(FFABS(s->plane[0].stride), FFABS(s->plane[1].stride), FFABS(s->plane[2].stride))) < 0)
            return AVERROR(ENOMEM);

        /* [DIRAC_STD] 11.1 Picture parse. picture_parse() */
        ret = dirac_decode_picture_header(s);
        if (ret < 0)
            return ret;

        /* [DIRAC_STD] 13.0 Transform data syntax. transform_data() */
        ret = dirac_decode_frame_internal(s);
        if (ret < 0)
            return ret;
    }
    return 0;
}