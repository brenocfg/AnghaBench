#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int channels; scalar_t__ bps; scalar_t__ samplerate; scalar_t__ max_blocksize; } ;
struct TYPE_15__ {int channels; scalar_t__ bits_per_raw_sample; scalar_t__ sample_rate; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  channel_layout; } ;
struct TYPE_14__ {int got_streaminfo; TYPE_8__ flac_stream_info; TYPE_4__* avctx; int /*<<< orphan*/  dsp; scalar_t__ blocksize; int /*<<< orphan*/  ch_mode; int /*<<< orphan*/  gb; } ;
struct TYPE_13__ {int channels; scalar_t__ bps; scalar_t__ samplerate; scalar_t__ blocksize; int /*<<< orphan*/  ch_mode; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ FLACFrameInfo ;
typedef  TYPE_2__ FLACContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ FLAC_MAX_BLOCKSIZE ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int allocate_buffers (TYPE_2__*) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int decode_subframe (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dump_headers (TYPE_4__*,TYPE_8__*) ; 
 int ff_flac_decode_frame_header (TYPE_4__*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_flac_set_channel_layout (TYPE_4__*) ; 
 int /*<<< orphan*/  ff_flacdsp_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  flac_set_bps (TYPE_2__*) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_frame(FLACContext *s)
{
    int i, ret;
    GetBitContext *gb = &s->gb;
    FLACFrameInfo fi;

    if ((ret = ff_flac_decode_frame_header(s->avctx, gb, &fi, 0)) < 0) {
        av_log(s->avctx, AV_LOG_ERROR, "invalid frame header\n");
        return ret;
    }

    if (   s->flac_stream_info.channels
        && fi.channels != s->flac_stream_info.channels
        && s->got_streaminfo) {
        s->flac_stream_info.channels = s->avctx->channels = fi.channels;
        ff_flac_set_channel_layout(s->avctx);
        ret = allocate_buffers(s);
        if (ret < 0)
            return ret;
    }
    s->flac_stream_info.channels = s->avctx->channels = fi.channels;
    if (!s->avctx->channel_layout)
        ff_flac_set_channel_layout(s->avctx);
    s->ch_mode = fi.ch_mode;

    if (!s->flac_stream_info.bps && !fi.bps) {
        av_log(s->avctx, AV_LOG_ERROR, "bps not found in STREAMINFO or frame header\n");
        return AVERROR_INVALIDDATA;
    }
    if (!fi.bps) {
        fi.bps = s->flac_stream_info.bps;
    } else if (s->flac_stream_info.bps && fi.bps != s->flac_stream_info.bps) {
        av_log(s->avctx, AV_LOG_ERROR, "switching bps mid-stream is not "
                                       "supported\n");
        return AVERROR_INVALIDDATA;
    }

    if (!s->flac_stream_info.bps) {
        s->flac_stream_info.bps = s->avctx->bits_per_raw_sample = fi.bps;
        flac_set_bps(s);
    }

    if (!s->flac_stream_info.max_blocksize)
        s->flac_stream_info.max_blocksize = FLAC_MAX_BLOCKSIZE;
    if (fi.blocksize > s->flac_stream_info.max_blocksize) {
        av_log(s->avctx, AV_LOG_ERROR, "blocksize %d > %d\n", fi.blocksize,
               s->flac_stream_info.max_blocksize);
        return AVERROR_INVALIDDATA;
    }
    s->blocksize = fi.blocksize;

    if (!s->flac_stream_info.samplerate && !fi.samplerate) {
        av_log(s->avctx, AV_LOG_ERROR, "sample rate not found in STREAMINFO"
                                        " or frame header\n");
        return AVERROR_INVALIDDATA;
    }
    if (fi.samplerate == 0)
        fi.samplerate = s->flac_stream_info.samplerate;
    s->flac_stream_info.samplerate = s->avctx->sample_rate = fi.samplerate;

    if (!s->got_streaminfo) {
        ret = allocate_buffers(s);
        if (ret < 0)
            return ret;
        s->got_streaminfo = 1;
        dump_headers(s->avctx, &s->flac_stream_info);
    }
    ff_flacdsp_init(&s->dsp, s->avctx->sample_fmt,
                    s->flac_stream_info.channels, s->flac_stream_info.bps);

//    dump_headers(s->avctx, &s->flac_stream_info);

    /* subframes */
    for (i = 0; i < s->flac_stream_info.channels; i++) {
        if ((ret = decode_subframe(s, i)) < 0)
            return ret;
    }

    align_get_bits(gb);

    /* frame footer */
    skip_bits(gb, 16); /* data crc */

    return 0;
}