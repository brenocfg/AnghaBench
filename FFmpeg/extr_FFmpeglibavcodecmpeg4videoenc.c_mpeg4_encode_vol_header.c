#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int num; int den; } ;
struct TYPE_8__ {int quarter_sample; int vo_type; int workaround_bugs; int aspect_ratio_info; int low_delay; int time_increment_bits; int width; int height; int mpeg_quant; int /*<<< orphan*/  pb; TYPE_2__* avctx; scalar_t__ data_partitioning; scalar_t__ rtp_mode; scalar_t__ progressive_sequence; scalar_t__ max_b_frames; } ;
struct TYPE_6__ {int den; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  inter_matrix; int /*<<< orphan*/  intra_matrix; TYPE_1__ time_base; TYPE_5__ sample_aspect_ratio; } ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int ADV_SIMPLE_VO_TYPE ; 
 int AV_CODEC_FLAG_BITEXACT ; 
 int /*<<< orphan*/  CONFIG_MPEG4_ENCODER ; 
 int FF_ASPECT_EXTENDED ; 
 int FF_BUG_MS ; 
 int /*<<< orphan*/  LIBAVCODEC_IDENT ; 
 int RECT_SHAPE ; 
 int SIMPLE_VO_TYPE ; 
 int /*<<< orphan*/  av_reduce (int*,int*,int,int,int) ; 
 int /*<<< orphan*/  avpriv_put_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_h263_aspect_to_info (TYPE_5__) ; 
 int /*<<< orphan*/  ff_mpeg4_stuffing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_write_quant_matrix (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void mpeg4_encode_vol_header(MpegEncContext *s,
                                    int vo_number,
                                    int vol_number)
{
    int vo_ver_id;

    if (!CONFIG_MPEG4_ENCODER)
        return;

    if (s->max_b_frames || s->quarter_sample) {
        vo_ver_id  = 5;
        s->vo_type = ADV_SIMPLE_VO_TYPE;
    } else {
        vo_ver_id  = 1;
        s->vo_type = SIMPLE_VO_TYPE;
    }

    put_bits(&s->pb, 16, 0);
    put_bits(&s->pb, 16, 0x100 + vo_number);        /* video obj */
    put_bits(&s->pb, 16, 0);
    put_bits(&s->pb, 16, 0x120 + vol_number);       /* video obj layer */

    put_bits(&s->pb, 1, 0);             /* random access vol */
    put_bits(&s->pb, 8, s->vo_type);    /* video obj type indication */
    if (s->workaround_bugs & FF_BUG_MS) {
        put_bits(&s->pb, 1, 0);         /* is obj layer id= no */
    } else {
        put_bits(&s->pb, 1, 1);         /* is obj layer id= yes */
        put_bits(&s->pb, 4, vo_ver_id); /* is obj layer ver id */
        put_bits(&s->pb, 3, 1);         /* is obj layer priority */
    }

    s->aspect_ratio_info = ff_h263_aspect_to_info(s->avctx->sample_aspect_ratio);

    put_bits(&s->pb, 4, s->aspect_ratio_info); /* aspect ratio info */
    if (s->aspect_ratio_info == FF_ASPECT_EXTENDED) {
        av_reduce(&s->avctx->sample_aspect_ratio.num, &s->avctx->sample_aspect_ratio.den,
                   s->avctx->sample_aspect_ratio.num,  s->avctx->sample_aspect_ratio.den, 255);
        put_bits(&s->pb, 8, s->avctx->sample_aspect_ratio.num);
        put_bits(&s->pb, 8, s->avctx->sample_aspect_ratio.den);
    }

    if (s->workaround_bugs & FF_BUG_MS) {
        put_bits(&s->pb, 1, 0);         /* vol control parameters= no @@@ */
    } else {
        put_bits(&s->pb, 1, 1);         /* vol control parameters= yes */
        put_bits(&s->pb, 2, 1);         /* chroma format YUV 420/YV12 */
        put_bits(&s->pb, 1, s->low_delay);
        put_bits(&s->pb, 1, 0);         /* vbv parameters= no */
    }

    put_bits(&s->pb, 2, RECT_SHAPE);    /* vol shape= rectangle */
    put_bits(&s->pb, 1, 1);             /* marker bit */

    put_bits(&s->pb, 16, s->avctx->time_base.den);
    if (s->time_increment_bits < 1)
        s->time_increment_bits = 1;
    put_bits(&s->pb, 1, 1);             /* marker bit */
    put_bits(&s->pb, 1, 0);             /* fixed vop rate=no */
    put_bits(&s->pb, 1, 1);             /* marker bit */
    put_bits(&s->pb, 13, s->width);     /* vol width */
    put_bits(&s->pb, 1, 1);             /* marker bit */
    put_bits(&s->pb, 13, s->height);    /* vol height */
    put_bits(&s->pb, 1, 1);             /* marker bit */
    put_bits(&s->pb, 1, s->progressive_sequence ? 0 : 1);
    put_bits(&s->pb, 1, 1);             /* obmc disable */
    if (vo_ver_id == 1)
        put_bits(&s->pb, 1, 0);       /* sprite enable */
    else
        put_bits(&s->pb, 2, 0);       /* sprite enable */

    put_bits(&s->pb, 1, 0);             /* not 8 bit == false */
    put_bits(&s->pb, 1, s->mpeg_quant); /* quant type = (0 = H.263 style) */

    if (s->mpeg_quant) {
        ff_write_quant_matrix(&s->pb, s->avctx->intra_matrix);
        ff_write_quant_matrix(&s->pb, s->avctx->inter_matrix);
    }

    if (vo_ver_id != 1)
        put_bits(&s->pb, 1, s->quarter_sample);
    put_bits(&s->pb, 1, 1);             /* complexity estimation disable */
    put_bits(&s->pb, 1, s->rtp_mode ? 0 : 1); /* resync marker disable */
    put_bits(&s->pb, 1, s->data_partitioning ? 1 : 0);
    if (s->data_partitioning)
        put_bits(&s->pb, 1, 0);         /* no rvlc */

    if (vo_ver_id != 1) {
        put_bits(&s->pb, 1, 0);         /* newpred */
        put_bits(&s->pb, 1, 0);         /* reduced res vop */
    }
    put_bits(&s->pb, 1, 0);             /* scalability */

    ff_mpeg4_stuffing(&s->pb);

    /* user data */
    if (!(s->avctx->flags & AV_CODEC_FLAG_BITEXACT)) {
        put_bits(&s->pb, 16, 0);
        put_bits(&s->pb, 16, 0x1B2);    /* user_data */
        avpriv_put_string(&s->pb, LIBAVCODEC_IDENT, 0);
    }
}