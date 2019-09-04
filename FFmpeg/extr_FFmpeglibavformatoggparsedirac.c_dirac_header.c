#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct ogg_stream {scalar_t__ psize; scalar_t__ pstart; scalar_t__ buf; } ;
struct ogg {struct ogg_stream* streams; } ;
struct TYPE_12__ {int num; int /*<<< orphan*/  den; } ;
struct TYPE_15__ {TYPE_2__ framerate; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  level; int /*<<< orphan*/  profile; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  color_primaries; int /*<<< orphan*/  color_trc; int /*<<< orphan*/  color_range; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_14__ {TYPE_3__** streams; struct ogg* priv_data; } ;
struct TYPE_13__ {int /*<<< orphan*/  sample_aspect_ratio; TYPE_1__* codecpar; } ;
struct TYPE_11__ {scalar_t__ codec_id; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  level; int /*<<< orphan*/  profile; int /*<<< orphan*/  color_space; int /*<<< orphan*/  color_primaries; int /*<<< orphan*/  color_trc; int /*<<< orphan*/  color_range; int /*<<< orphan*/  format; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVDiracSeqHeader ;

/* Variables and functions */
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_DIRAC ; 
 int av_dirac_parse_sequence_header (TYPE_5__**,scalar_t__,scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  av_freep (TYPE_5__**) ; 
 scalar_t__ av_image_check_sar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dirac_header(AVFormatContext *s, int idx)
{
    struct ogg *ogg = s->priv_data;
    struct ogg_stream *os = ogg->streams + idx;
    AVStream *st = s->streams[idx];
    AVDiracSeqHeader *dsh;
    int ret;

    // already parsed the header
    if (st->codecpar->codec_id == AV_CODEC_ID_DIRAC)
        return 0;

    ret = av_dirac_parse_sequence_header(&dsh, os->buf + os->pstart + 13, (os->psize - 13), s);
    if (ret < 0)
        return ret;

    st->codecpar->codec_type      = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id        = AV_CODEC_ID_DIRAC;
    st->codecpar->width           = dsh->width;
    st->codecpar->height          = dsh->height;
    st->codecpar->format          = dsh->pix_fmt;
    st->codecpar->color_range     = dsh->color_range;
    st->codecpar->color_trc       = dsh->color_trc;
    st->codecpar->color_primaries = dsh->color_primaries;
    st->codecpar->color_space     = dsh->colorspace;
    st->codecpar->profile         = dsh->profile;
    st->codecpar->level           = dsh->level;
    if (av_image_check_sar(st->codecpar->width, st->codecpar->height, dsh->sample_aspect_ratio) >= 0)
        st->sample_aspect_ratio = dsh->sample_aspect_ratio;

    // Dirac in Ogg always stores timestamps as though the video were interlaced
    avpriv_set_pts_info(st, 64, dsh->framerate.den, 2 * dsh->framerate.num);

    av_freep(&dsh);
    return 1;
}