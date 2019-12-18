#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_16__ {int nb_streams; int /*<<< orphan*/  channel_maps; } ;
struct TYPE_15__ {int frame_count; int frame_duration; } ;
struct TYPE_14__ {scalar_t__ extradata; } ;
struct TYPE_13__ {int duration; TYPE_2__* priv_data; } ;
struct TYPE_11__ {int frame_start_found; int state; } ;
struct TYPE_12__ {int ts_framing; int extradata_parsed; TYPE_7__ pkt; TYPE_9__ ctx; TYPE_1__ pc; } ;
typedef  TYPE_1__ ParseContext ;
typedef  TYPE_2__ OpusParseContext ;
typedef  TYPE_3__ AVCodecParserContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RB16 (int const*) ; 
 int END_NOT_FOUND ; 
 int OPUS_TS_HEADER ; 
 int OPUS_TS_MASK ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int ff_opus_parse_extradata (TYPE_4__*,TYPE_9__*) ; 
 int ff_opus_parse_packet (TYPE_7__*,int const*,int,int) ; 
 int* parse_opus_ts_header (int const*,int*,int) ; 

__attribute__((used)) static int opus_find_frame_end(AVCodecParserContext *ctx, AVCodecContext *avctx,
                               const uint8_t *buf, int buf_size, int *header_len)
{
    OpusParseContext *s = ctx->priv_data;
    ParseContext *pc    = &s->pc;
    int ret, start_found, i = 0, payload_len = 0;
    const uint8_t *payload;
    uint32_t state;
    uint16_t hdr;
    *header_len = 0;

    if (!buf_size)
        return 0;

    start_found = pc->frame_start_found;
    state = pc->state;
    payload = buf;

    /* Check if we're using Opus in MPEG-TS framing */
    if (!s->ts_framing && buf_size > 2) {
        hdr = AV_RB16(buf);
        if ((hdr & OPUS_TS_MASK) == OPUS_TS_HEADER)
            s->ts_framing = 1;
    }

    if (s->ts_framing && !start_found) {
        for (i = 0; i < buf_size-2; i++) {
            state = (state << 8) | payload[i];
            if ((state & OPUS_TS_MASK) == OPUS_TS_HEADER) {
                payload = parse_opus_ts_header(payload, &payload_len, buf_size - i);
                if (!payload) {
                    av_log(avctx, AV_LOG_ERROR, "Error parsing Ogg TS header.\n");
                    return AVERROR_INVALIDDATA;
                }
                *header_len = payload - buf;
                start_found = 1;
                break;
            }
        }
    }

    if (!s->ts_framing)
        payload_len = buf_size;

    if (avctx->extradata && !s->extradata_parsed) {
        ret = ff_opus_parse_extradata(avctx, &s->ctx);
        if (ret < 0) {
            av_log(avctx, AV_LOG_ERROR, "Error parsing Ogg extradata.\n");
            return AVERROR_INVALIDDATA;
        }
        av_freep(&s->ctx.channel_maps);
        s->extradata_parsed = 1;
    }

    if (payload_len <= buf_size && (!s->ts_framing || start_found)) {
        ret = ff_opus_parse_packet(&s->pkt, payload, payload_len, s->ctx.nb_streams > 1);
        if (ret < 0) {
            av_log(avctx, AV_LOG_ERROR, "Error parsing Opus packet header.\n");
            pc->frame_start_found = 0;
            return AVERROR_INVALIDDATA;
        }

        ctx->duration = s->pkt.frame_count * s->pkt.frame_duration;
    }

    if (s->ts_framing) {
        if (start_found) {
            if (payload_len + *header_len <= buf_size) {
                pc->frame_start_found = 0;
                pc->state             = -1;
                return payload_len + *header_len;
            }
        }

        pc->frame_start_found = start_found;
        pc->state = state;
        return END_NOT_FOUND;
    }

    return buf_size;
}