#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* avctx; } ;
typedef  TYPE_2__ V4L2m2mContext ;
typedef  int /*<<< orphan*/  V4L2Context ;
struct TYPE_4__ {int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 int FFALIGN (int,int const) ; 
 scalar_t__ av_codec_is_decoder (int /*<<< orphan*/ ) ; 
 TYPE_2__* ctx_to_m2mctx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int v4l2_get_framesize_compressed(V4L2Context* ctx, int width, int height)
{
    V4L2m2mContext *s = ctx_to_m2mctx(ctx);
    const int SZ_4K = 0x1000;
    int size;

    if (s->avctx && av_codec_is_decoder(s->avctx->codec))
        return ((width * height * 3 / 2) / 2) + 128;

    /* encoder */
    size = FFALIGN(height, 32) * FFALIGN(width, 32) * 3 / 2 / 2;
    return FFALIGN(size, SZ_4K);
}