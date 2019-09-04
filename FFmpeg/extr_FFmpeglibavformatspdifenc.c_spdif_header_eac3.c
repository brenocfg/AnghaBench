#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {int* data; scalar_t__ size; } ;
struct TYPE_6__ {size_t hd_buf_filled; int hd_buf_count; int pkt_offset; size_t out_bytes; size_t length_code; int /*<<< orphan*/ * hd_buf; int /*<<< orphan*/ * out_buf; int /*<<< orphan*/  data_type; int /*<<< orphan*/  hd_buf_size; } ;
typedef  TYPE_1__ IEC61937Context ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  IEC61937_EAC3 ; 
 int /*<<< orphan*/ * av_fast_realloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,scalar_t__) ; 

__attribute__((used)) static int spdif_header_eac3(AVFormatContext *s, AVPacket *pkt)
{
    IEC61937Context *ctx = s->priv_data;
    static const uint8_t eac3_repeat[4] = {6, 3, 2, 1};
    int repeat = 1;

    int bsid = pkt->data[5] >> 3;
    if (bsid > 10 && (pkt->data[4] & 0xc0) != 0xc0) /* fscod */
        repeat = eac3_repeat[(pkt->data[4] & 0x30) >> 4]; /* numblkscod */

    ctx->hd_buf = av_fast_realloc(ctx->hd_buf, &ctx->hd_buf_size, ctx->hd_buf_filled + pkt->size);
    if (!ctx->hd_buf)
        return AVERROR(ENOMEM);

    memcpy(&ctx->hd_buf[ctx->hd_buf_filled], pkt->data, pkt->size);

    ctx->hd_buf_filled += pkt->size;
    if (++ctx->hd_buf_count < repeat){
        ctx->pkt_offset = 0;
        return 0;
    }
    ctx->data_type   = IEC61937_EAC3;
    ctx->pkt_offset  = 24576;
    ctx->out_buf     = ctx->hd_buf;
    ctx->out_bytes   = ctx->hd_buf_filled;
    ctx->length_code = ctx->hd_buf_filled;

    ctx->hd_buf_count  = 0;
    ctx->hd_buf_filled = 0;
    return 0;
}