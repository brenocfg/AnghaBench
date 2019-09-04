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
struct TYPE_6__ {TYPE_1__** outputs; int /*<<< orphan*/ * priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
typedef  int /*<<< orphan*/  FieldMatchContext ;
typedef  int /*<<< orphan*/  const AVFrame ;
typedef  TYPE_1__ AVFilterLink ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* av_frame_clone (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  av_frame_copy_props (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  copy_fields (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  const* ff_get_video_buffer (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  mB 131 
 int mC ; 
#define  mN 130 
#define  mP 129 
#define  mU 128 

__attribute__((used)) static AVFrame *create_weave_frame(AVFilterContext *ctx, int match, int field,
                                   const AVFrame *prv, AVFrame *src, const AVFrame *nxt)
{
    AVFrame *dst;
    FieldMatchContext *fm = ctx->priv;

    if (match == mC) {
        dst = av_frame_clone(src);
    } else {
        AVFilterLink *outlink = ctx->outputs[0];

        dst = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!dst)
            return NULL;
        av_frame_copy_props(dst, src);

        switch (match) {
        case mP: copy_fields(fm, dst, src, 1-field); copy_fields(fm, dst, prv,   field); break;
        case mN: copy_fields(fm, dst, src, 1-field); copy_fields(fm, dst, nxt,   field); break;
        case mB: copy_fields(fm, dst, src,   field); copy_fields(fm, dst, prv, 1-field); break;
        case mU: copy_fields(fm, dst, src,   field); copy_fields(fm, dst, nxt, 1-field); break;
        default: av_assert0(0);
        }
    }
    return dst;
}