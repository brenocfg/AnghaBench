#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* priv_data; } ;
struct TYPE_13__ {TYPE_1__* codecpar; } ;
struct TYPE_12__ {int /*<<< orphan*/  nports; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_11__ {int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ JackData ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_F32BE ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_F32LE ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int start_jack (TYPE_4__*) ; 
 int /*<<< orphan*/  stop_jack (TYPE_2__*) ; 

__attribute__((used)) static int audio_read_header(AVFormatContext *context)
{
    JackData *self = context->priv_data;
    AVStream *stream;
    int test;

    if ((test = start_jack(context)))
        return test;

    stream = avformat_new_stream(context, NULL);
    if (!stream) {
        stop_jack(self);
        return AVERROR(ENOMEM);
    }

    stream->codecpar->codec_type   = AVMEDIA_TYPE_AUDIO;
#if HAVE_BIGENDIAN
    stream->codecpar->codec_id     = AV_CODEC_ID_PCM_F32BE;
#else
    stream->codecpar->codec_id     = AV_CODEC_ID_PCM_F32LE;
#endif
    stream->codecpar->sample_rate  = self->sample_rate;
    stream->codecpar->channels     = self->nports;

    avpriv_set_pts_info(stream, 64, 1, 1000000);  /* 64 bits pts in us */
    return 0;
}