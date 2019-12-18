#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int npixels; int /*<<< orphan*/ * frm0; int /*<<< orphan*/  buf_size; } ;
typedef  TYPE_1__ SANMVideoContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  av_bswap16 (int /*<<< orphan*/ ) ; 
 scalar_t__ rle_decode (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_5(SANMVideoContext *ctx)
{
#if HAVE_BIGENDIAN
    uint16_t *frm;
    int npixels;
#endif
    uint8_t *dst = (uint8_t*)ctx->frm0;

    if (rle_decode(ctx, dst, ctx->buf_size))
        return AVERROR_INVALIDDATA;

#if HAVE_BIGENDIAN
    npixels = ctx->npixels;
    frm = ctx->frm0;
    while (npixels--) {
        *frm = av_bswap16(*frm);
        frm++;
    }
#endif

    return 0;
}