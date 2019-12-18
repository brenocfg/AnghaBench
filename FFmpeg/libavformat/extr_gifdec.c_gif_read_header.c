#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_19__ {int /*<<< orphan*/  str; } ;
struct TYPE_18__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/ * pb; TYPE_3__* priv_data; } ;
struct TYPE_17__ {int duration; int nb_frames; TYPE_2__* codecpar; scalar_t__ start_time; } ;
struct TYPE_16__ {int delay; int default_delay; int min_delay; int /*<<< orphan*/  max_delay; } ;
struct TYPE_14__ {int num; int den; } ;
struct TYPE_15__ {int width; int height; TYPE_1__ sample_aspect_ratio; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_3__ GIFDemuxContext ;
typedef  TYPE_4__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;
typedef  TYPE_6__ AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CODEC_ID_GIF ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 int GIF_COM_EXT_LABEL ; 
 int GIF_EXTENSION_INTRODUCER ; 
 int GIF_GCE_EXT_LABEL ; 
 int GIF_IMAGE_SEPARATOR ; 
 int GIF_TRAILER ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_read_to_bprint (int /*<<< orphan*/ *,TYPE_6__*,int) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_4__*,int,int,int) ; 
 int /*<<< orphan*/  gif_skip_subblocks (int /*<<< orphan*/ *) ; 
 int resync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gif_read_header(AVFormatContext *s)
{
    GIFDemuxContext *gdc = s->priv_data;
    AVIOContext     *pb  = s->pb;
    AVStream        *st;
    int type, width, height, ret, n, flags;
    int64_t nb_frames = 0, duration = 0;

    if ((ret = resync(pb)) < 0)
        return ret;

    gdc->delay  = gdc->default_delay;
    width  = avio_rl16(pb);
    height = avio_rl16(pb);
    flags = avio_r8(pb);
    avio_skip(pb, 1);
    n      = avio_r8(pb);

    if (width == 0 || height == 0)
        return AVERROR_INVALIDDATA;

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    if (flags & 0x80)
        avio_skip(pb, 3 * (1 << ((flags & 0x07) + 1)));

    while ((type = avio_r8(pb)) != GIF_TRAILER) {
        if (avio_feof(pb))
            break;
        if (type == GIF_EXTENSION_INTRODUCER) {
            int subtype = avio_r8(pb);
            if (subtype == GIF_COM_EXT_LABEL) {
                AVBPrint bp;
                int block_size;

                av_bprint_init(&bp, 0, -1);
                while ((block_size = avio_r8(pb)) != 0) {
                    avio_read_to_bprint(pb, &bp, block_size);
                }
                av_dict_set(&s->metadata, "comment", bp.str, 0);
                av_bprint_finalize(&bp, NULL);
            } else if (subtype == GIF_GCE_EXT_LABEL) {
                int block_size = avio_r8(pb);

                if (block_size == 4) {
                    int delay;

                    avio_skip(pb, 1);
                    delay = avio_rl16(pb);
                    if (delay < gdc->min_delay)
                        delay = gdc->default_delay;
                    delay = FFMIN(delay, gdc->max_delay);
                    duration += delay;
                    avio_skip(pb, 1);
                } else {
                    avio_skip(pb, block_size);
                }
                gif_skip_subblocks(pb);
            } else {
                gif_skip_subblocks(pb);
            }
        } else if (type == GIF_IMAGE_SEPARATOR) {
            avio_skip(pb, 8);
            flags = avio_r8(pb);
            if (flags & 0x80)
                avio_skip(pb, 3 * (1 << ((flags & 0x07) + 1)));
            avio_skip(pb, 1);
            gif_skip_subblocks(pb);
            nb_frames++;
        } else {
            break;
        }
    }

    /* GIF format operates with time in "hundredths of second",
     * therefore timebase is 1/100 */
    avpriv_set_pts_info(st, 64, 1, 100);
    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id   = AV_CODEC_ID_GIF;
    st->codecpar->width      = width;
    st->codecpar->height     = height;
    st->start_time           = 0;
    st->duration             = duration;
    st->nb_frames            = nb_frames;
    if (n) {
        st->codecpar->sample_aspect_ratio.num = n + 15;
        st->codecpar->sample_aspect_ratio.den = 64;
    }

    /* jump to start because gif decoder needs header data too */
    if (avio_seek(pb, 0, SEEK_SET) != 0)
        return AVERROR(EIO);

    return 0;
}