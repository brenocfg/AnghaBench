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
struct TYPE_18__ {scalar_t__ codec_id; scalar_t__ codec_tag; } ;
struct TYPE_17__ {int nb_streams; TYPE_2__** streams; TYPE_1__* oformat; int /*<<< orphan*/  flags; int /*<<< orphan*/  io_open; int /*<<< orphan*/  io_close; int /*<<< orphan*/  opaque; int /*<<< orphan*/  metadata; int /*<<< orphan*/  max_delay; int /*<<< orphan*/  interrupt_callback; TYPE_3__* priv_data; } ;
struct TYPE_16__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/  time_base; int /*<<< orphan*/  sample_aspect_ratio; TYPE_6__* codecpar; } ;
struct TYPE_15__ {TYPE_5__* avf; int /*<<< orphan*/  oformat; } ;
struct TYPE_14__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/  time_base; int /*<<< orphan*/  sample_aspect_ratio; TYPE_6__* codecpar; } ;
struct TYPE_13__ {int /*<<< orphan*/  codec_tag; } ;
typedef  TYPE_3__ SegmentContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVFormatContext ;
typedef  TYPE_6__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ av_codec_get_id (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ av_codec_get_tag (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_parameters_copy (TYPE_6__*,TYPE_6__*) ; 
 int avformat_alloc_output_context2 (TYPE_5__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int segment_mux_init(AVFormatContext *s)
{
    SegmentContext *seg = s->priv_data;
    AVFormatContext *oc;
    int i;
    int ret;

    ret = avformat_alloc_output_context2(&seg->avf, seg->oformat, NULL, NULL);
    if (ret < 0)
        return ret;
    oc = seg->avf;

    oc->interrupt_callback = s->interrupt_callback;
    oc->max_delay          = s->max_delay;
    av_dict_copy(&oc->metadata, s->metadata, 0);
    oc->opaque             = s->opaque;
    oc->io_close           = s->io_close;
    oc->io_open            = s->io_open;
    oc->flags              = s->flags;

    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st;
        AVCodecParameters *ipar, *opar;

        if (!(st = avformat_new_stream(oc, NULL)))
            return AVERROR(ENOMEM);
        ipar = s->streams[i]->codecpar;
        opar = st->codecpar;
        avcodec_parameters_copy(opar, ipar);
        if (!oc->oformat->codec_tag ||
            av_codec_get_id (oc->oformat->codec_tag, ipar->codec_tag) == opar->codec_id ||
            av_codec_get_tag(oc->oformat->codec_tag, ipar->codec_id) <= 0) {
            opar->codec_tag = ipar->codec_tag;
        } else {
            opar->codec_tag = 0;
        }
        st->sample_aspect_ratio = s->streams[i]->sample_aspect_ratio;
        st->time_base = s->streams[i]->time_base;
        av_dict_copy(&st->metadata, s->streams[i]->metadata, 0);
    }

    return 0;
}