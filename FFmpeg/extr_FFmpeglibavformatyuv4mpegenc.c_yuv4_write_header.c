#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* priv_data; int nb_streams; TYPE_2__** streams; int /*<<< orphan*/  strict_std_compliance; } ;
struct TYPE_7__ {TYPE_1__* codecpar; } ;
struct TYPE_6__ {scalar_t__ codec_id; int format; } ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_WRAPPED_AVFRAME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
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
 int /*<<< orphan*/  FF_COMPLIANCE_NORMAL ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int yuv4_write_header(AVFormatContext *s)
{
    int *first_pkt = s->priv_data;

    if (s->nb_streams != 1)
        return AVERROR(EIO);

    if (s->streams[0]->codecpar->codec_id != AV_CODEC_ID_WRAPPED_AVFRAME) {
        av_log(s, AV_LOG_ERROR, "ERROR: Codec not supported.\n");
        return AVERROR_INVALIDDATA;
    }

    switch (s->streams[0]->codecpar->format) {
    case AV_PIX_FMT_YUV411P:
        av_log(s, AV_LOG_WARNING, "Warning: generating rarely used 4:1:1 YUV "
               "stream, some mjpegtools might not work.\n");
        break;
    case AV_PIX_FMT_GRAY8:
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
        if (s->strict_std_compliance >= FF_COMPLIANCE_NORMAL) {
            av_log(s, AV_LOG_ERROR, "'%s' is not an official yuv4mpegpipe pixel format. "
                   "Use '-strict -1' to encode to this pixel format.\n",
                   av_get_pix_fmt_name(s->streams[0]->codecpar->format));
            return AVERROR(EINVAL);
        }
        av_log(s, AV_LOG_WARNING, "Warning: generating non standard YUV stream. "
               "Mjpegtools will not work.\n");
        break;
    default:
        av_log(s, AV_LOG_ERROR, "ERROR: yuv4mpeg can only handle "
               "yuv444p, yuv422p, yuv420p, yuv411p and gray8 pixel formats. "
               "And using 'strict -1' also yuv444p9, yuv422p9, yuv420p9, "
               "yuv444p10, yuv422p10, yuv420p10, "
               "yuv444p12, yuv422p12, yuv420p12, "
               "yuv444p14, yuv422p14, yuv420p14, "
               "yuv444p16, yuv422p16, yuv420p16, "
               "gray9, gray10, gray12 "
               "and gray16 pixel formats. "
               "Use -pix_fmt to select one.\n");
        return AVERROR(EIO);
    }

    *first_pkt = 1;
    return 0;
}