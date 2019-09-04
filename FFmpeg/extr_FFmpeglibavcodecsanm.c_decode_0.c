#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int width; int height; int /*<<< orphan*/  pitch; int /*<<< orphan*/  gb; int /*<<< orphan*/  avctx; int /*<<< orphan*/ * frm0; } ;
typedef  TYPE_1__ SANMVideoContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_le16u (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_0(SANMVideoContext *ctx)
{
    uint16_t *frm = ctx->frm0;
    int x, y;

    if (bytestream2_get_bytes_left(&ctx->gb) < ctx->width * ctx->height * 2) {
        av_log(ctx->avctx, AV_LOG_ERROR, "Insufficient data for raw frame.\n");
        return AVERROR_INVALIDDATA;
    }
    for (y = 0; y < ctx->height; y++) {
        for (x = 0; x < ctx->width; x++)
            frm[x] = bytestream2_get_le16u(&ctx->gb);
        frm += ctx->pitch;
    }
    return 0;
}