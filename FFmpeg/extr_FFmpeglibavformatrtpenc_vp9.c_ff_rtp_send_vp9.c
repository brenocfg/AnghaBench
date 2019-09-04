#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int* buf_ptr; int* buf; scalar_t__ max_payload_size; int /*<<< orphan*/  cur_timestamp; int /*<<< orphan*/  timestamp; } ;
typedef  TYPE_1__ RTPMuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int FFMIN (int,scalar_t__) ; 
 scalar_t__ RTP_VP9_DESC_REQUIRED_SIZE ; 
 int /*<<< orphan*/  ff_rtp_send_data (TYPE_2__*,int*,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int) ; 

void ff_rtp_send_vp9(AVFormatContext *ctx, const uint8_t *buf, int size)
{
    RTPMuxContext *rtp_ctx = ctx->priv_data;
    int len;

    rtp_ctx->timestamp  = rtp_ctx->cur_timestamp;
    rtp_ctx->buf_ptr    = rtp_ctx->buf;

    /* mark the first fragment */
    *rtp_ctx->buf_ptr++ = 0x08;

    while (size > 0) {
        len = FFMIN(size, rtp_ctx->max_payload_size - RTP_VP9_DESC_REQUIRED_SIZE);

        if (len == size) {
            /* mark the last fragment */
            rtp_ctx->buf[0] |= 0x04;
        }

        memcpy(rtp_ctx->buf_ptr, buf, len);
        ff_rtp_send_data(ctx, rtp_ctx->buf, len + RTP_VP9_DESC_REQUIRED_SIZE, size == len);

        size            -= len;
        buf             += len;

        /* clear the end bit */
        rtp_ctx->buf[0] &= ~0x08;
    }
}