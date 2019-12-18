#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_16__ {scalar_t__ codec_id; int channels; } ;
struct TYPE_15__ {int /*<<< orphan*/  pb; TYPE_2__* priv_data; TYPE_1__** streams; } ;
struct TYPE_14__ {int duration; scalar_t__ stream_index; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {scalar_t__ current_block; scalar_t__ block_count; int last_block_used_bytes; int last_block_samples; int last_block_size; int block_size; int samples_per_block; scalar_t__ adpc; scalar_t__ table; } ;
struct TYPE_12__ {TYPE_5__* codecpar; } ;
typedef  TYPE_2__ BRSTMDemuxContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_ADPCM_THP ; 
 scalar_t__ AV_CODEC_ID_ADPCM_THP_LE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT_MAX ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_mallocz (int) ; 
 scalar_t__ av_new_packet (TYPE_3__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ ) ; 
 int avio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bytestream_put_be32 (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  bytestream_put_buffer (int /*<<< orphan*/ **,scalar_t__,int) ; 
 int /*<<< orphan*/  bytestream_put_le32 (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static int read_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVCodecParameters *par = s->streams[0]->codecpar;
    BRSTMDemuxContext *b = s->priv_data;
    uint32_t samples, size, skip = 0;
    int ret, i;

    if (avio_feof(s->pb))
        return AVERROR_EOF;
    b->current_block++;
    if (b->current_block == b->block_count) {
        size    = b->last_block_used_bytes;
        samples = b->last_block_samples;
        skip    = b->last_block_size - b->last_block_used_bytes;

        if (samples < size * 14 / 8) {
            uint32_t adjusted_size = samples / 14 * 8;
            if (samples % 14)
                adjusted_size += (samples % 14 + 1) / 2 + 1;

            skip += size - adjusted_size;
            size = adjusted_size;
        }
    } else if (b->current_block < b->block_count) {
        size    = b->block_size;
        samples = b->samples_per_block;
    } else {
        return AVERROR_EOF;
    }

    if (par->codec_id == AV_CODEC_ID_ADPCM_THP ||
        par->codec_id == AV_CODEC_ID_ADPCM_THP_LE) {
        uint8_t *dst;

        if (!b->adpc) {
            av_log(s, AV_LOG_ERROR, "adpcm_thp requires ADPC chunk, but none was found.\n");
            return AVERROR_INVALIDDATA;
        }
        if (!b->table) {
            b->table = av_mallocz(32 * par->channels);
            if (!b->table)
                return AVERROR(ENOMEM);
        }

        if (size > (INT_MAX - 32 - 4) ||
            (32 + 4 + size) > (INT_MAX / par->channels) ||
            (32 + 4 + size) * par->channels > INT_MAX - 8)
            return AVERROR_INVALIDDATA;
        if (av_new_packet(pkt, 8 + (32 + 4 + size) * par->channels) < 0)
            return AVERROR(ENOMEM);
        dst = pkt->data;
        if (par->codec_id == AV_CODEC_ID_ADPCM_THP_LE) {
            bytestream_put_le32(&dst, size * par->channels);
            bytestream_put_le32(&dst, samples);
        } else {
            bytestream_put_be32(&dst, size * par->channels);
            bytestream_put_be32(&dst, samples);
        }
        bytestream_put_buffer(&dst, b->table, 32 * par->channels);
        bytestream_put_buffer(&dst, b->adpc + 4 * par->channels *
                                    (b->current_block - 1), 4 * par->channels);

        for (i = 0; i < par->channels; i++) {
            ret = avio_read(s->pb, dst, size);
            dst += size;
            avio_skip(s->pb, skip);
            if (ret != size) {
                av_packet_unref(pkt);
                break;
            }
        }
        pkt->duration = samples;
    } else {
        size *= par->channels;
        ret = av_get_packet(s->pb, pkt, size);
    }

    pkt->stream_index = 0;

    if (ret != size)
        ret = AVERROR(EIO);

    return ret;
}