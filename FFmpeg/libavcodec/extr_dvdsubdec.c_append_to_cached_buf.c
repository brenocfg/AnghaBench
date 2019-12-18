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
struct TYPE_5__ {int buf_size; scalar_t__ buf; } ;
typedef  TYPE_1__ DVDSubContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int append_to_cached_buf(AVCodecContext *avctx,
                                const uint8_t *buf, int buf_size)
{
    DVDSubContext *ctx = avctx->priv_data;

    av_assert0(buf_size >= 0 && ctx->buf_size <= sizeof(ctx->buf));
    if (buf_size >= sizeof(ctx->buf) - ctx->buf_size) {
        av_log(avctx, AV_LOG_WARNING, "Attempt to reconstruct "
               "too large SPU packets aborted.\n");
        ctx->buf_size = 0;
        return AVERROR_INVALIDDATA;
    }
    memcpy(ctx->buf + ctx->buf_size, buf, buf_size);
    ctx->buf_size += buf_size;
    return 0;
}