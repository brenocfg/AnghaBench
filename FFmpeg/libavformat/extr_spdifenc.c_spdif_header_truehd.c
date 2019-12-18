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
typedef  int /*<<< orphan*/  mat_start_code ;
typedef  int /*<<< orphan*/  mat_middle_code ;
typedef  int /*<<< orphan*/  mat_end_code ;
struct TYPE_9__ {TYPE_1__* priv_data; } ;
struct TYPE_8__ {int size; char const* data; } ;
struct TYPE_7__ {int hd_buf_count; int pkt_offset; int out_bytes; int length_code; int /*<<< orphan*/ * hd_buf; int /*<<< orphan*/ * out_buf; int /*<<< orphan*/  data_type; } ;
typedef  TYPE_1__ IEC61937Context ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 int BURST_HEADER_SIZE ; 
 int /*<<< orphan*/  IEC61937_TRUEHD ; 
 int MAT_FRAME_SIZE ; 
 int MAT_MIDDLE_CODE_OFFSET ; 
 int TRUEHD_FRAME_OFFSET ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int spdif_header_truehd(AVFormatContext *s, AVPacket *pkt)
{
    IEC61937Context *ctx = s->priv_data;
    int mat_code_length = 0;
    static const char mat_end_code[16] = { 0xC3, 0xC2, 0xC0, 0xC4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x97, 0x11 };

    if (!ctx->hd_buf_count) {
        static const char mat_start_code[20] = { 0x07, 0x9E, 0x00, 0x03, 0x84, 0x01, 0x01, 0x01, 0x80, 0x00, 0x56, 0xA5, 0x3B, 0xF4, 0x81, 0x83, 0x49, 0x80, 0x77, 0xE0 };
        mat_code_length = sizeof(mat_start_code) + BURST_HEADER_SIZE;
        memcpy(ctx->hd_buf, mat_start_code, sizeof(mat_start_code));

    } else if (ctx->hd_buf_count == 12) {
        static const char mat_middle_code[12] = { 0xC3, 0xC1, 0x42, 0x49, 0x3B, 0xFA, 0x82, 0x83, 0x49, 0x80, 0x77, 0xE0 };
        mat_code_length = sizeof(mat_middle_code) + MAT_MIDDLE_CODE_OFFSET;
        memcpy(&ctx->hd_buf[12 * TRUEHD_FRAME_OFFSET - BURST_HEADER_SIZE + MAT_MIDDLE_CODE_OFFSET],
               mat_middle_code, sizeof(mat_middle_code));
    }

    if (pkt->size > TRUEHD_FRAME_OFFSET - mat_code_length) {
        /* if such frames exist, we'd need some more complex logic to
         * distribute the TrueHD frames in the MAT frame */
        avpriv_request_sample(s, "Too large TrueHD frame of %d bytes",
                              pkt->size);
        return AVERROR_PATCHWELCOME;
    }

    memcpy(&ctx->hd_buf[ctx->hd_buf_count * TRUEHD_FRAME_OFFSET - BURST_HEADER_SIZE + mat_code_length],
           pkt->data, pkt->size);
    if (ctx->hd_buf_count < 23) {
        memset(&ctx->hd_buf[ctx->hd_buf_count * TRUEHD_FRAME_OFFSET - BURST_HEADER_SIZE + mat_code_length + pkt->size],
               0, TRUEHD_FRAME_OFFSET - pkt->size - mat_code_length);
    } else {
        size_t padding = MAT_FRAME_SIZE - (ctx->hd_buf_count * TRUEHD_FRAME_OFFSET - BURST_HEADER_SIZE + pkt->size);
        memset(&ctx->hd_buf[MAT_FRAME_SIZE - padding], 0, padding);
    }

    if (++ctx->hd_buf_count < 24){
        ctx->pkt_offset = 0;
        return 0;
    }
    memcpy(&ctx->hd_buf[MAT_FRAME_SIZE - sizeof(mat_end_code)], mat_end_code, sizeof(mat_end_code));
    ctx->hd_buf_count = 0;

    ctx->data_type   = IEC61937_TRUEHD;
    ctx->pkt_offset  = 61440;
    ctx->out_buf     = ctx->hd_buf;
    ctx->out_bytes   = MAT_FRAME_SIZE;
    ctx->length_code = MAT_FRAME_SIZE;
    return 0;
}