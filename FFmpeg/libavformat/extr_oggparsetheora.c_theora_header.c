#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ogg_stream {int psize; int* buf; size_t pstart; TYPE_3__* private; } ;
struct ogg {struct ogg_stream* streams; } ;
struct TYPE_15__ {int version; int gpshift; unsigned int gpmask; } ;
typedef  TYPE_3__ TheoraParams ;
struct TYPE_18__ {TYPE_4__** streams; struct ogg* priv_data; } ;
struct TYPE_17__ {int den; int num; } ;
struct TYPE_13__ {void* den; void* num; } ;
struct TYPE_16__ {TYPE_2__* codecpar; int /*<<< orphan*/  need_parsing; TYPE_1__ sample_aspect_ratio; } ;
struct TYPE_14__ {int extradata_size; int width; int height; int /*<<< orphan*/ * extradata; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVRational ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AVSTREAM_PARSE_HEADERS ; 
 int /*<<< orphan*/  AV_CODEC_ID_THEORA ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* av_mallocz (int) ; 
 int av_reallocp (int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_4__*,int,int,int) ; 
 int /*<<< orphan*/  ff_vorbis_stream_comment (TYPE_6__*,TYPE_4__*,int*,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int theora_header(AVFormatContext *s, int idx)
{
    struct ogg *ogg       = s->priv_data;
    struct ogg_stream *os = ogg->streams + idx;
    AVStream *st          = s->streams[idx];
    TheoraParams *thp     = os->private;
    int cds               = st->codecpar->extradata_size + os->psize + 2;
    int err;
    uint8_t *cdp;

    if (!(os->buf[os->pstart] & 0x80))
        return 0;

    if (!thp) {
        thp = av_mallocz(sizeof(*thp));
        if (!thp)
            return AVERROR(ENOMEM);
        os->private = thp;
    }

    switch (os->buf[os->pstart]) {
    case 0x80: {
        GetBitContext gb;
        AVRational timebase;

        init_get_bits(&gb, os->buf + os->pstart, os->psize * 8);

        /* 0x80"theora" */
        skip_bits_long(&gb, 7 * 8);

        thp->version = get_bits_long(&gb, 24);
        if (thp->version < 0x030100) {
            av_log(s, AV_LOG_ERROR,
                   "Too old or unsupported Theora (%x)\n", thp->version);
            return AVERROR(ENOSYS);
        }

        st->codecpar->width  = get_bits(&gb, 16) << 4;
        st->codecpar->height = get_bits(&gb, 16) << 4;

        if (thp->version >= 0x030400)
            skip_bits(&gb, 100);

        if (thp->version >= 0x030200) {
            int width  = get_bits_long(&gb, 24);
            int height = get_bits_long(&gb, 24);
            if (width  <= st->codecpar->width  && width  > st->codecpar->width  - 16 &&
                height <= st->codecpar->height && height > st->codecpar->height - 16) {
                st->codecpar->width  = width;
                st->codecpar->height = height;
            }

            skip_bits(&gb, 16);
        }

        timebase.den = get_bits_long(&gb, 32);
        timebase.num = get_bits_long(&gb, 32);
        if (!(timebase.num > 0 && timebase.den > 0)) {
            av_log(s, AV_LOG_WARNING, "Invalid time base in theora stream, assuming 25 FPS\n");
            timebase.num = 1;
            timebase.den = 25;
        }
        avpriv_set_pts_info(st, 64, timebase.num, timebase.den);

        st->sample_aspect_ratio.num = get_bits_long(&gb, 24);
        st->sample_aspect_ratio.den = get_bits_long(&gb, 24);

        if (thp->version >= 0x030200)
            skip_bits_long(&gb, 38);
        if (thp->version >= 0x304000)
            skip_bits(&gb, 2);

        thp->gpshift = get_bits(&gb, 5);
        thp->gpmask  = (1U << thp->gpshift) - 1;

        st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
        st->codecpar->codec_id   = AV_CODEC_ID_THEORA;
        st->need_parsing      = AVSTREAM_PARSE_HEADERS;
    }
    break;
    case 0x81:
        ff_vorbis_stream_comment(s, st, os->buf + os->pstart + 7, os->psize - 7);
    case 0x82:
        if (!thp->version)
            return AVERROR_INVALIDDATA;
        break;
    default:
        av_log(s, AV_LOG_ERROR, "Unknown header type %X\n", os->buf[os->pstart]);
        return AVERROR_INVALIDDATA;
    }

    if ((err = av_reallocp(&st->codecpar->extradata,
                           cds + AV_INPUT_BUFFER_PADDING_SIZE)) < 0) {
        st->codecpar->extradata_size = 0;
        return err;
    }
    memset(st->codecpar->extradata + cds, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    cdp    = st->codecpar->extradata + st->codecpar->extradata_size;
    *cdp++ = os->psize >> 8;
    *cdp++ = os->psize & 0xff;
    memcpy(cdp, os->buf + os->pstart, os->psize);
    st->codecpar->extradata_size = cds;

    return 1;
}