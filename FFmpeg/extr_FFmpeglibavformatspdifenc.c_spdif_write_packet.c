#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct AVFormatContext {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_7__ {int* data; int size; } ;
struct TYPE_6__ {int* out_buf; int out_bytes; int length_code; int use_preamble; int extra_bswap; int (* header_info ) (struct AVFormatContext*,TYPE_2__*) ;int pkt_offset; int data_type; int spdif_flags; int* buffer; int /*<<< orphan*/  buffer_size; } ;
typedef  TYPE_1__ IEC61937Context ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int BURST_HEADER_SIZE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (int,int) ; 
 int SPDIF_FLAG_BIGENDIAN ; 
 int SYNCWORD1 ; 
 int SYNCWORD2 ; 
 int /*<<< orphan*/  av_fast_malloc (int**,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  av_log (struct AVFormatContext*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ff_spdif_bswap_buf16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spdif_put_16 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct AVFormatContext*,TYPE_2__*) ; 

__attribute__((used)) static int spdif_write_packet(struct AVFormatContext *s, AVPacket *pkt)
{
    IEC61937Context *ctx = s->priv_data;
    int ret, padding;

    ctx->out_buf = pkt->data;
    ctx->out_bytes = pkt->size;
    ctx->length_code = FFALIGN(pkt->size, 2) << 3;
    ctx->use_preamble = 1;
    ctx->extra_bswap = 0;

    ret = ctx->header_info(s, pkt);
    if (ret < 0)
        return ret;
    if (!ctx->pkt_offset)
        return 0;

    padding = (ctx->pkt_offset - ctx->use_preamble * BURST_HEADER_SIZE - ctx->out_bytes) & ~1;
    if (padding < 0) {
        av_log(s, AV_LOG_ERROR, "bitrate is too high\n");
        return AVERROR(EINVAL);
    }

    if (ctx->use_preamble) {
        spdif_put_16(ctx, s->pb, SYNCWORD1);       //Pa
        spdif_put_16(ctx, s->pb, SYNCWORD2);       //Pb
        spdif_put_16(ctx, s->pb, ctx->data_type);  //Pc
        spdif_put_16(ctx, s->pb, ctx->length_code);//Pd
    }

    if (ctx->extra_bswap ^ (ctx->spdif_flags & SPDIF_FLAG_BIGENDIAN)) {
        avio_write(s->pb, ctx->out_buf, ctx->out_bytes & ~1);
    } else {
        av_fast_malloc(&ctx->buffer, &ctx->buffer_size, ctx->out_bytes + AV_INPUT_BUFFER_PADDING_SIZE);
        if (!ctx->buffer)
            return AVERROR(ENOMEM);
        ff_spdif_bswap_buf16((uint16_t *)ctx->buffer, (uint16_t *)ctx->out_buf, ctx->out_bytes >> 1);
        avio_write(s->pb, ctx->buffer, ctx->out_bytes & ~1);
    }

    /* a final lone byte has to be MSB aligned */
    if (ctx->out_bytes & 1)
        spdif_put_16(ctx, s->pb, ctx->out_buf[ctx->out_bytes - 1] << 8);

    ffio_fill(s->pb, 0, padding);

    av_log(s, AV_LOG_DEBUG, "type=%x len=%i pkt_offset=%i\n",
           ctx->data_type, ctx->out_bytes, ctx->pkt_offset);

    return 0;
}