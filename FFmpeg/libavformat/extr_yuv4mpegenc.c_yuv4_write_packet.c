#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_14__ {int* priv_data; int /*<<< orphan*/ * pb; TYPE_2__** streams; } ;
struct TYPE_13__ {char** data; int /*<<< orphan*/ * linesize; } ;
struct TYPE_12__ {size_t stream_index; scalar_t__ data; } ;
struct TYPE_11__ {TYPE_1__* codecpar; } ;
struct TYPE_10__ {int width; int height; int format; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CEIL_RSHIFT (int,int) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  Y4M_FRAME_MAGIC ; 
 int /*<<< orphan*/  Y4M_LINE_MAX ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_pix_fmt_get_chroma_sub_sample (int const,int*,int*) ; 
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,char*,int) ; 
 int strlen (char*) ; 
 scalar_t__ yuv4_generate_header (TYPE_5__*,char*) ; 

__attribute__((used)) static int yuv4_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVStream *st = s->streams[pkt->stream_index];
    AVIOContext *pb = s->pb;
    AVFrame *frame;
    int* first_pkt = s->priv_data;
    int width, height, h_chroma_shift, v_chroma_shift;
    int i;
    char buf2[Y4M_LINE_MAX + 1];
    uint8_t *ptr, *ptr1, *ptr2;

    frame = (AVFrame *)pkt->data;

    /* for the first packet we have to output the header as well */
    if (*first_pkt) {
        *first_pkt = 0;
        if (yuv4_generate_header(s, buf2) < 0) {
            av_log(s, AV_LOG_ERROR,
                   "Error. YUV4MPEG stream header write failed.\n");
            return AVERROR(EIO);
        } else {
            avio_write(pb, buf2, strlen(buf2));
        }
    }

    /* construct frame header */

    avio_printf(s->pb, "%s\n", Y4M_FRAME_MAGIC);

    width  = st->codecpar->width;
    height = st->codecpar->height;

    ptr = frame->data[0];

    switch (st->codecpar->format) {
    case AV_PIX_FMT_GRAY8:
    case AV_PIX_FMT_YUV411P:
    case AV_PIX_FMT_YUV420P:
    case AV_PIX_FMT_YUV422P:
    case AV_PIX_FMT_YUV444P:
    // TODO: remove YUVJ pixel formats when they are completely removed from the codebase.
    case AV_PIX_FMT_YUVJ420P:
    case AV_PIX_FMT_YUVJ422P:
    case AV_PIX_FMT_YUVJ444P:
        break;
    case AV_PIX_FMT_GRAY9:
    case AV_PIX_FMT_GRAY10:
    case AV_PIX_FMT_GRAY12:
    case AV_PIX_FMT_GRAY16:
    case AV_PIX_FMT_YUV420P9:
    case AV_PIX_FMT_YUV422P9:
    case AV_PIX_FMT_YUV444P9:
    case AV_PIX_FMT_YUV420P10:
    case AV_PIX_FMT_YUV422P10:
    case AV_PIX_FMT_YUV444P10:
    case AV_PIX_FMT_YUV420P12:
    case AV_PIX_FMT_YUV422P12:
    case AV_PIX_FMT_YUV444P12:
    case AV_PIX_FMT_YUV420P14:
    case AV_PIX_FMT_YUV422P14:
    case AV_PIX_FMT_YUV444P14:
    case AV_PIX_FMT_YUV420P16:
    case AV_PIX_FMT_YUV422P16:
    case AV_PIX_FMT_YUV444P16:
        width *= 2;
        break;
    default:
        av_log(s, AV_LOG_ERROR, "The pixel format '%s' is not supported.\n",
               av_get_pix_fmt_name(st->codecpar->format));
        return AVERROR(EINVAL);
    }

    for (i = 0; i < height; i++) {
        avio_write(pb, ptr, width);
        ptr += frame->linesize[0];
    }

    if (st->codecpar->format != AV_PIX_FMT_GRAY8 && st->codecpar->format != AV_PIX_FMT_GRAY9 &&
        st->codecpar->format != AV_PIX_FMT_GRAY10 && st->codecpar->format != AV_PIX_FMT_GRAY12 &&
        st->codecpar->format != AV_PIX_FMT_GRAY16) {
        // Adjust for smaller Cb and Cr planes
        av_pix_fmt_get_chroma_sub_sample(st->codecpar->format, &h_chroma_shift,
                                         &v_chroma_shift);
        // Shift right, rounding up
        width  = AV_CEIL_RSHIFT(width,  h_chroma_shift);
        height = AV_CEIL_RSHIFT(height, v_chroma_shift);

        ptr1 = frame->data[1];
        ptr2 = frame->data[2];
        for (i = 0; i < height; i++) {     /* Cb */
            avio_write(pb, ptr1, width);
            ptr1 += frame->linesize[1];
        }
        for (i = 0; i < height; i++) {     /* Cr */
            avio_write(pb, ptr2, width);
            ptr2 += frame->linesize[2];
        }
    }

    return 0;
}