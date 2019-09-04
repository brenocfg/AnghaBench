#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtshd_start_code ;
struct TYPE_9__ {TYPE_1__* priv_data; } ;
struct TYPE_8__ {int size; char const* data; } ;
struct TYPE_7__ {int dtshd_rate; int pkt_offset; int data_type; int dtshd_skip; int dtshd_fallback; int out_bytes; scalar_t__ hd_buf; scalar_t__ out_buf; int /*<<< orphan*/  hd_buf_size; scalar_t__ length_code; } ;
typedef  TYPE_1__ IEC61937Context ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_WB16 (scalar_t__,int) ; 
 int BURST_HEADER_SIZE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ FFALIGN (int,int) ; 
 int IEC61937_DTSHD ; 
 int /*<<< orphan*/  av_fast_malloc (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 int spdif_dts4_subtype (int) ; 

__attribute__((used)) static int spdif_header_dts4(AVFormatContext *s, AVPacket *pkt, int core_size,
                             int sample_rate, int blocks)
{
    IEC61937Context *ctx = s->priv_data;
    static const char dtshd_start_code[10] = { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xfe };
    int pkt_size = pkt->size;
    int period;
    int subtype;

    if (!core_size) {
        av_log(s, AV_LOG_ERROR, "HD mode not supported for this format\n");
        return AVERROR(EINVAL);
    }

    if (!sample_rate) {
        av_log(s, AV_LOG_ERROR, "Unknown DTS sample rate for HD\n");
        return AVERROR_INVALIDDATA;
    }

    period = ctx->dtshd_rate * (blocks << 5) / sample_rate;
    subtype = spdif_dts4_subtype(period);

    if (subtype < 0) {
        av_log(s, AV_LOG_ERROR, "Specified HD rate of %d Hz would require an "
               "impossible repetition period of %d for the current DTS stream"
               " (blocks = %d, sample rate = %d)\n", ctx->dtshd_rate, period,
               blocks << 5, sample_rate);
        return AVERROR(EINVAL);
    }

    /* set pkt_offset and DTS IV subtype according to the requested output
     * rate */
    ctx->pkt_offset = period * 4;
    ctx->data_type = IEC61937_DTSHD | subtype << 8;

    /* If the bitrate is too high for transmitting at the selected
     * repetition period setting, strip DTS-HD until a good amount
     * of consecutive non-overflowing HD frames have been observed.
     * This generally only happens if the caller is cramming a Master
     * Audio stream into 192kHz IEC 60958 (which may or may not fit). */
    if (sizeof(dtshd_start_code) + 2 + pkt_size
            > ctx->pkt_offset - BURST_HEADER_SIZE && core_size) {
        if (!ctx->dtshd_skip)
            av_log(s, AV_LOG_WARNING, "DTS-HD bitrate too high, "
                                      "temporarily sending core only\n");
        if (ctx->dtshd_fallback > 0)
            ctx->dtshd_skip = sample_rate * ctx->dtshd_fallback / (blocks << 5);
        else
            /* skip permanently (dtshd_fallback == -1) or just once
             * (dtshd_fallback == 0) */
            ctx->dtshd_skip = 1;
    }
    if (ctx->dtshd_skip && core_size) {
        pkt_size = core_size;
        if (ctx->dtshd_fallback >= 0)
            --ctx->dtshd_skip;
    }

    ctx->out_bytes   = sizeof(dtshd_start_code) + 2 + pkt_size;

    /* Align so that (length_code & 0xf) == 0x8. This is reportedly needed
     * with some receivers, but the exact requirement is unconfirmed. */
    ctx->length_code = FFALIGN(ctx->out_bytes + 0x8, 0x10) - 0x8;

    av_fast_malloc(&ctx->hd_buf, &ctx->hd_buf_size, ctx->out_bytes);
    if (!ctx->hd_buf)
        return AVERROR(ENOMEM);

    ctx->out_buf = ctx->hd_buf;

    memcpy(ctx->hd_buf, dtshd_start_code, sizeof(dtshd_start_code));
    AV_WB16(ctx->hd_buf + sizeof(dtshd_start_code), pkt_size);
    memcpy(ctx->hd_buf + sizeof(dtshd_start_code) + 2, pkt->data, pkt_size);

    return 0;
}