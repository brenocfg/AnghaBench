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
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int sliding; int xpos; int xend; scalar_t__ phase; scalar_t__ magnitude; } ;
typedef  TYPE_1__ SpectrumSynthContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
#define  FULLFRAME 131 
#define  REPLACE 130 
#define  RSCROLL 129 
#define  SCROLL 128 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_free (scalar_t__*) ; 
 int try_push_frame (TYPE_2__*,int) ; 

__attribute__((used)) static int try_push_frames(AVFilterContext *ctx)
{
    SpectrumSynthContext *s = ctx->priv;
    int ret, x;

    if (!(s->magnitude && s->phase))
        return 0;

    switch (s->sliding) {
    case REPLACE:
        ret = try_push_frame(ctx, s->xpos);
        s->xpos++;
        if (s->xpos >= s->xend)
            s->xpos = 0;
        break;
    case SCROLL:
        s->xpos = s->xend - 1;
        ret = try_push_frame(ctx, s->xpos);
        break;
    case RSCROLL:
        s->xpos = 0;
        ret = try_push_frame(ctx, s->xpos);
        break;
    case FULLFRAME:
        for (x = 0; x < s->xend; x++) {
            ret = try_push_frame(ctx, x);
            if (ret < 0)
                break;
        }
        break;
    default:
        av_assert0(0);
    }

    av_frame_free(&s->magnitude);
    av_frame_free(&s->phase);
    return ret;
}