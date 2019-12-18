#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_17__ {scalar_t__ bits_per_coded_sample; scalar_t__ channels; int /*<<< orphan*/  codec_id; } ;
struct TYPE_16__ {size_t stream_index; scalar_t__ pts; scalar_t__ size; } ;
struct TYPE_15__ {int /*<<< orphan*/  time_base; TYPE_2__* priv_data; } ;
struct TYPE_14__ {TYPE_1__* fc; } ;
struct TYPE_13__ {scalar_t__ sample_count; int /*<<< orphan*/  edit_rate; } ;
struct TYPE_12__ {TYPE_4__** streams; } ;
typedef  TYPE_2__ MXFTrack ;
typedef  TYPE_3__ MXFContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVCodecParameters ;

/* Variables and functions */
 scalar_t__ av_get_bits_per_sample (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_inv_q (int /*<<< orphan*/ ) ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mxf_compute_sample_count (TYPE_3__*,TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static int mxf_set_audio_pts(MXFContext *mxf, AVCodecParameters *par,
                             AVPacket *pkt)
{
    AVStream *st = mxf->fc->streams[pkt->stream_index];
    MXFTrack *track = st->priv_data;
    int64_t bits_per_sample = par->bits_per_coded_sample;

    if (!bits_per_sample)
        bits_per_sample = av_get_bits_per_sample(par->codec_id);

    pkt->pts = track->sample_count;

    if (   par->channels <= 0
        || bits_per_sample <= 0
        || par->channels * (int64_t)bits_per_sample < 8)
        track->sample_count = mxf_compute_sample_count(mxf, st, av_rescale_q(track->sample_count, st->time_base, av_inv_q(track->edit_rate)) + 1);
    else
        track->sample_count += pkt->size / (par->channels * (int64_t)bits_per_sample / 8);

    return 0;
}