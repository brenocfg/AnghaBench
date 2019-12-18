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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int pass_pos; int /*<<< orphan*/ * pass_data; int /*<<< orphan*/  pass_size; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ librav1eContext ;
struct TYPE_9__ {int /*<<< orphan*/  stats_out; TYPE_1__* priv_data; } ;
struct TYPE_8__ {int len; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ RaData ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 size_t AV_BASE64_SIZE (int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_base64_encode (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * av_fast_realloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rav1e_data_unref (TYPE_2__*) ; 
 TYPE_2__* rav1e_twopass_out (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_stats(AVCodecContext *avctx, int eos)
{
    librav1eContext *ctx = avctx->priv_data;
    RaData* buf = rav1e_twopass_out(ctx->ctx);
    if (!buf)
        return 0;

    if (!eos) {
        uint8_t *tmp = av_fast_realloc(ctx->pass_data, &ctx->pass_size,
                                      ctx->pass_pos + buf->len);
        if (!tmp) {
            rav1e_data_unref(buf);
            return AVERROR(ENOMEM);
        }

        ctx->pass_data = tmp;
        memcpy(ctx->pass_data + ctx->pass_pos, buf->data, buf->len);
        ctx->pass_pos += buf->len;
    } else {
        size_t b64_size = AV_BASE64_SIZE(ctx->pass_pos);

        memcpy(ctx->pass_data, buf->data, buf->len);

        avctx->stats_out = av_malloc(b64_size);
        if (!avctx->stats_out) {
            rav1e_data_unref(buf);
            return AVERROR(ENOMEM);
        }

        av_base64_encode(avctx->stats_out, b64_size, ctx->pass_data, ctx->pass_pos);

        av_freep(&ctx->pass_data);
    }

    rav1e_data_unref(buf);

    return 0;
}