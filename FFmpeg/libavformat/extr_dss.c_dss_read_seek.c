#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_4__ {scalar_t__ audio_codec; int packet_size; int swap; int dss_sp_swap_byte; scalar_t__ counter; scalar_t__ dss_header_size; } ;
typedef  TYPE_1__ DSSDemuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ DSS_ACODEC_DSS_SP ; 
 int DSS_AUDIO_BLOCK_HEADER_SIZE ; 
 scalar_t__ DSS_BLOCK_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ ,int*,int) ; 
 int avio_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int avio_skip (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dss_read_seek(AVFormatContext *s, int stream_index,
                         int64_t timestamp, int flags)
{
    DSSDemuxContext *ctx = s->priv_data;
    int64_t ret, seekto;
    uint8_t header[DSS_AUDIO_BLOCK_HEADER_SIZE];
    int offset;

    if (ctx->audio_codec == DSS_ACODEC_DSS_SP)
        seekto = timestamp / 264 * 41 / 506 * 512;
    else
        seekto = timestamp / 240 * ctx->packet_size / 506 * 512;

    if (seekto < 0)
        seekto = 0;

    seekto += ctx->dss_header_size;

    ret = avio_seek(s->pb, seekto, SEEK_SET);
    if (ret < 0)
        return ret;

    avio_read(s->pb, header, DSS_AUDIO_BLOCK_HEADER_SIZE);
    ctx->swap = !!(header[0] & 0x80);
    offset = 2*header[1] + 2*ctx->swap;
    if (offset < DSS_AUDIO_BLOCK_HEADER_SIZE)
        return AVERROR_INVALIDDATA;
    if (offset == DSS_AUDIO_BLOCK_HEADER_SIZE) {
        ctx->counter = 0;
        offset = avio_skip(s->pb, -DSS_AUDIO_BLOCK_HEADER_SIZE);
    } else {
        ctx->counter = DSS_BLOCK_SIZE - offset;
        offset = avio_skip(s->pb, offset - DSS_AUDIO_BLOCK_HEADER_SIZE);
    }
    ctx->dss_sp_swap_byte = -1;
    return 0;
}