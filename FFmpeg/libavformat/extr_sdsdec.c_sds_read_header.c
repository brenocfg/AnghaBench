#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_11__ {int duration; TYPE_1__* codecpar; } ;
struct TYPE_10__ {int bit_depth; int size; int /*<<< orphan*/  read_block; } ;
struct TYPE_9__ {int channels; int sample_rate; int /*<<< orphan*/  codec_type; int /*<<< orphan*/  codec_id; } ;
typedef  TYPE_2__ SDSContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_U32LE ; 
 int /*<<< orphan*/  ENOMEM ; 
 unsigned int SDS_3BYTE_TO_INT_DECODE (unsigned int) ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 unsigned int avio_rl24 (int /*<<< orphan*/ *) ; 
 int avio_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  byte2_read ; 
 int /*<<< orphan*/  byte3_read ; 
 int /*<<< orphan*/  byte4_read ; 

__attribute__((used)) static int sds_read_header(AVFormatContext *ctx)
{
    SDSContext *s = ctx->priv_data;
    unsigned sample_period;
    AVIOContext *pb = ctx->pb;
    AVStream *st;

    st = avformat_new_stream(ctx, NULL);
    if (!st)
        return AVERROR(ENOMEM);

    avio_skip(pb, 4);
    avio_skip(pb, 2);

    s->bit_depth = avio_r8(pb);
    if (s->bit_depth < 8 || s->bit_depth > 28)
        return AVERROR_INVALIDDATA;

    if (s->bit_depth < 14) {
        s->read_block = byte2_read;
        s->size = 60 * 4;
    } else if (s->bit_depth < 21) {
        s->read_block = byte3_read;
        s->size = 40 * 4;
    } else {
        s->read_block = byte4_read;
        s->size = 30 * 4;
    }
    st->codecpar->codec_id = AV_CODEC_ID_PCM_U32LE;

    sample_period = avio_rl24(pb);
    sample_period = SDS_3BYTE_TO_INT_DECODE(sample_period);
    avio_skip(pb, 11);

    st->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    st->codecpar->channels = 1;
    st->codecpar->sample_rate = sample_period ? 1000000000 / sample_period : 16000;
    st->duration = (avio_size(pb) - 21) / (127) * s->size / 4;

    avpriv_set_pts_info(st, 64, 1, st->codecpar->sample_rate);

    return 0;
}