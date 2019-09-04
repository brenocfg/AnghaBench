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
typedef  enum perm { ____Placeholder_perm } perm ;
struct TYPE_8__ {int /*<<< orphan*/ * outputs; TYPE_1__* priv; } ;
struct TYPE_7__ {TYPE_3__* dst; } ;
struct TYPE_6__ {int mode; int /*<<< orphan*/  lfg; } ;
typedef  TYPE_1__ PermsContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  ENOMEM ; 
#define  MODE_RANDOM 131 
#define  MODE_RO 130 
#define  MODE_RW 129 
#define  MODE_TOGGLE 128 
 int RO ; 
 int RW ; 
 int /*<<< orphan*/ * av_frame_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 scalar_t__ av_frame_is_writable (int /*<<< orphan*/ *) ; 
 int av_frame_make_writable (int /*<<< orphan*/ *) ; 
 int av_lfg_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * perm_str ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *frame)
{
    int ret;
    AVFilterContext *ctx = inlink->dst;
    PermsContext *s = ctx->priv;
    AVFrame *out = frame;
    enum perm in_perm = av_frame_is_writable(frame) ? RW : RO;
    enum perm out_perm;

    switch (s->mode) {
    case MODE_TOGGLE:   out_perm = in_perm == RO ? RW : RO;                 break;
    case MODE_RANDOM:   out_perm = av_lfg_get(&s->lfg) & 1 ? RW : RO;       break;
    case MODE_RO:       out_perm = RO;                                      break;
    case MODE_RW:       out_perm = RW;                                      break;
    default:            out_perm = in_perm;                                 break;
    }

    av_log(ctx, AV_LOG_VERBOSE, "%s -> %s%s\n",
           perm_str[in_perm], perm_str[out_perm],
           in_perm == out_perm ? " (no-op)" : "");

    if (in_perm == RO && out_perm == RW) {
        if ((ret = av_frame_make_writable(frame)) < 0)
            return ret;
    } else if (in_perm == RW && out_perm == RO) {
        out = av_frame_clone(frame);
        if (!out)
            return AVERROR(ENOMEM);
    }

    ret = ff_filter_frame(ctx->outputs[0], out);

    if (in_perm == RW && out_perm == RO)
        av_frame_free(&frame);
    return ret;
}