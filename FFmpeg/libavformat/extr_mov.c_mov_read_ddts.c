#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_9__ {int nb_streams; TYPE_3__** streams; } ;
struct TYPE_8__ {TYPE_1__* codecpar; } ;
struct TYPE_7__ {TYPE_5__* fc; } ;
struct TYPE_6__ {scalar_t__ sample_rate; int frame_size; int channel_layout; int /*<<< orphan*/  channels; void* bits_per_coded_sample; void* bit_rate; } ;
typedef  TYPE_2__ MOVContext ;
typedef  int /*<<< orphan*/  MOVAtom ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AV_CH_FRONT_CENTER ; 
 int AV_CH_FRONT_LEFT ; 
 int AV_CH_FRONT_RIGHT ; 
 int AV_CH_LOW_FREQUENCY ; 
 int AV_CH_SIDE_LEFT ; 
 int AV_CH_SIDE_RIGHT ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_get_channel_layout_nb_channels (int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * av_malloc (scalar_t__) ; 
 int const avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int const) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mov_read_ddts(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    const uint32_t ddts_size = 20;
    AVStream *st = NULL;
    uint8_t *buf = NULL;
    uint32_t frame_duration_code = 0;
    uint32_t channel_layout_code = 0;
    GetBitContext gb;

    buf = av_malloc(ddts_size + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!buf) {
        return AVERROR(ENOMEM);
    }
    if (avio_read(pb, buf, ddts_size) < ddts_size) {
        av_free(buf);
        return AVERROR_INVALIDDATA;
    }

    init_get_bits(&gb, buf, 8*ddts_size);

    if (c->fc->nb_streams < 1) {
        av_free(buf);
        return 0;
    }
    st = c->fc->streams[c->fc->nb_streams-1];

    st->codecpar->sample_rate = get_bits_long(&gb, 32);
    if (st->codecpar->sample_rate <= 0) {
        av_log(c->fc, AV_LOG_ERROR, "Invalid sample rate %d\n", st->codecpar->sample_rate);
        av_free(buf);
        return AVERROR_INVALIDDATA;
    }
    skip_bits_long(&gb, 32); /* max bitrate */
    st->codecpar->bit_rate = get_bits_long(&gb, 32);
    st->codecpar->bits_per_coded_sample = get_bits(&gb, 8);
    frame_duration_code = get_bits(&gb, 2);
    skip_bits(&gb, 30); /* various fields */
    channel_layout_code = get_bits(&gb, 16);

    st->codecpar->frame_size =
            (frame_duration_code == 0) ? 512 :
            (frame_duration_code == 1) ? 1024 :
            (frame_duration_code == 2) ? 2048 :
            (frame_duration_code == 3) ? 4096 : 0;

    if (channel_layout_code > 0xff) {
        av_log(c->fc, AV_LOG_WARNING, "Unsupported DTS audio channel layout");
    }
    st->codecpar->channel_layout =
            ((channel_layout_code & 0x1) ? AV_CH_FRONT_CENTER : 0) |
            ((channel_layout_code & 0x2) ? AV_CH_FRONT_LEFT : 0) |
            ((channel_layout_code & 0x2) ? AV_CH_FRONT_RIGHT : 0) |
            ((channel_layout_code & 0x4) ? AV_CH_SIDE_LEFT : 0) |
            ((channel_layout_code & 0x4) ? AV_CH_SIDE_RIGHT : 0) |
            ((channel_layout_code & 0x8) ? AV_CH_LOW_FREQUENCY : 0);

    st->codecpar->channels = av_get_channel_layout_nb_channels(st->codecpar->channel_layout);
    av_free(buf);

    return 0;
}