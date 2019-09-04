#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__** streams; } ;
struct TYPE_8__ {int num; int den; } ;
struct TYPE_7__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
struct TYPE_10__ {TYPE_3__* codecpar; TYPE_2__ sample_aspect_ratio; TYPE_1__ time_base; } ;
struct TYPE_9__ {int width; int height; int field_order; int color_range; int format; int /*<<< orphan*/  chroma_location; } ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
#define  AVCHROMA_LOC_LEFT 162 
#define  AVCHROMA_LOC_TOPLEFT 161 
#define  AVCOL_RANGE_JPEG 160 
#define  AVCOL_RANGE_MPEG 159 
#define  AV_FIELD_BB 158 
#define  AV_FIELD_BT 157 
#define  AV_FIELD_TB 156 
#define  AV_FIELD_TT 155 
#define  AV_PIX_FMT_GRAY10 154 
#define  AV_PIX_FMT_GRAY12 153 
#define  AV_PIX_FMT_GRAY16 152 
#define  AV_PIX_FMT_GRAY8 151 
#define  AV_PIX_FMT_GRAY9 150 
#define  AV_PIX_FMT_YUV411P 149 
#define  AV_PIX_FMT_YUV420P 148 
#define  AV_PIX_FMT_YUV420P10 147 
#define  AV_PIX_FMT_YUV420P12 146 
#define  AV_PIX_FMT_YUV420P14 145 
#define  AV_PIX_FMT_YUV420P16 144 
#define  AV_PIX_FMT_YUV420P9 143 
#define  AV_PIX_FMT_YUV422P 142 
#define  AV_PIX_FMT_YUV422P10 141 
#define  AV_PIX_FMT_YUV422P12 140 
#define  AV_PIX_FMT_YUV422P14 139 
#define  AV_PIX_FMT_YUV422P16 138 
#define  AV_PIX_FMT_YUV422P9 137 
#define  AV_PIX_FMT_YUV444P 136 
#define  AV_PIX_FMT_YUV444P10 135 
#define  AV_PIX_FMT_YUV444P12 134 
#define  AV_PIX_FMT_YUV444P14 133 
#define  AV_PIX_FMT_YUV444P16 132 
#define  AV_PIX_FMT_YUV444P9 131 
#define  AV_PIX_FMT_YUVJ420P 130 
#define  AV_PIX_FMT_YUVJ422P 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  Y4M_LINE_MAX ; 
 char* Y4M_MAGIC ; 
 int /*<<< orphan*/  av_reduce (int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,char*,int,int,int,int,char,int,int,char const*,char const*) ; 

__attribute__((used)) static int yuv4_generate_header(AVFormatContext *s, char* buf)
{
    AVStream *st;
    int width, height;
    int raten, rated, aspectn, aspectd, n;
    char inter;
    const char *colorspace = "";
    const char *colorrange = "";
    int field_order;

    st     = s->streams[0];
    width  = st->codecpar->width;
    height = st->codecpar->height;
    field_order = st->codecpar->field_order;

    // TODO: should be avg_frame_rate
    av_reduce(&raten, &rated, st->time_base.den,
              st->time_base.num, (1UL << 31) - 1);

    aspectn = st->sample_aspect_ratio.num;
    aspectd = st->sample_aspect_ratio.den;

    if (aspectn == 0 && aspectd == 1)
        aspectd = 0;  // 0:0 means unknown

#if FF_API_LAVF_AVCTX
    FF_DISABLE_DEPRECATION_WARNINGS
    if (field_order != st->codec->field_order && st->codec->field_order != AV_FIELD_UNKNOWN)
        field_order = st->codec->field_order;
    FF_ENABLE_DEPRECATION_WARNINGS
#endif

    switch(st->codecpar->color_range) {
    case AVCOL_RANGE_MPEG:
        colorrange = " XCOLORRANGE=LIMITED";
        break;
    case AVCOL_RANGE_JPEG:
        colorrange = " XCOLORRANGE=FULL";
        break;
    default:
        break;
    }

    switch (field_order) {
    case AV_FIELD_TB:
    case AV_FIELD_TT: inter = 't'; break;
    case AV_FIELD_BT:
    case AV_FIELD_BB: inter = 'b'; break;
    default:          inter = 'p'; break;
    }

    switch (st->codecpar->format) {
    case AV_PIX_FMT_GRAY8:
        colorspace = " Cmono";
        break;
    case AV_PIX_FMT_GRAY9:
        colorspace = " Cmono9";
        break;
    case AV_PIX_FMT_GRAY10:
        colorspace = " Cmono10";
        break;
    case AV_PIX_FMT_GRAY12:
        colorspace = " Cmono12";
        break;
    case AV_PIX_FMT_GRAY16:
        colorspace = " Cmono16";
        break;
    case AV_PIX_FMT_YUV411P:
        colorspace = " C411 XYSCSS=411";
        break;
    case AV_PIX_FMT_YUVJ420P:
        colorspace = " C420jpeg XYSCSS=420JPEG";
        colorrange = " XCOLORRANGE=FULL";
        break;
    case AV_PIX_FMT_YUVJ422P:
        colorspace = " C422 XYSCSS=422";
        colorrange = " XCOLORRANGE=FULL";
        break;
    case AV_PIX_FMT_YUVJ444P:
        colorspace = " C444 XYSCSS=444";
        colorrange = " XCOLORRANGE=FULL";
        break;
    case AV_PIX_FMT_YUV420P:
        switch (st->codecpar->chroma_location) {
        case AVCHROMA_LOC_TOPLEFT: colorspace = " C420paldv XYSCSS=420PALDV"; break;
        case AVCHROMA_LOC_LEFT:    colorspace = " C420mpeg2 XYSCSS=420MPEG2"; break;
        default:                   colorspace = " C420jpeg XYSCSS=420JPEG";   break;
        }
        break;
    case AV_PIX_FMT_YUV422P:
        colorspace = " C422 XYSCSS=422";
        break;
    case AV_PIX_FMT_YUV444P:
        colorspace = " C444 XYSCSS=444";
        break;
    case AV_PIX_FMT_YUV420P9:
        colorspace = " C420p9 XYSCSS=420P9";
        break;
    case AV_PIX_FMT_YUV422P9:
        colorspace = " C422p9 XYSCSS=422P9";
        break;
    case AV_PIX_FMT_YUV444P9:
        colorspace = " C444p9 XYSCSS=444P9";
        break;
    case AV_PIX_FMT_YUV420P10:
        colorspace = " C420p10 XYSCSS=420P10";
        break;
    case AV_PIX_FMT_YUV422P10:
        colorspace = " C422p10 XYSCSS=422P10";
        break;
    case AV_PIX_FMT_YUV444P10:
        colorspace = " C444p10 XYSCSS=444P10";
        break;
    case AV_PIX_FMT_YUV420P12:
        colorspace = " C420p12 XYSCSS=420P12";
        break;
    case AV_PIX_FMT_YUV422P12:
        colorspace = " C422p12 XYSCSS=422P12";
        break;
    case AV_PIX_FMT_YUV444P12:
        colorspace = " C444p12 XYSCSS=444P12";
        break;
    case AV_PIX_FMT_YUV420P14:
        colorspace = " C420p14 XYSCSS=420P14";
        break;
    case AV_PIX_FMT_YUV422P14:
        colorspace = " C422p14 XYSCSS=422P14";
        break;
    case AV_PIX_FMT_YUV444P14:
        colorspace = " C444p14 XYSCSS=444P14";
        break;
    case AV_PIX_FMT_YUV420P16:
        colorspace = " C420p16 XYSCSS=420P16";
        break;
    case AV_PIX_FMT_YUV422P16:
        colorspace = " C422p16 XYSCSS=422P16";
        break;
    case AV_PIX_FMT_YUV444P16:
        colorspace = " C444p16 XYSCSS=444P16";
        break;
    }

    /* construct stream header, if this is the first frame */
    n = snprintf(buf, Y4M_LINE_MAX, "%s W%d H%d F%d:%d I%c A%d:%d%s%s\n",
                 Y4M_MAGIC, width, height, raten, rated, inter,
                 aspectn, aspectd, colorspace, colorrange);

    return n;
}