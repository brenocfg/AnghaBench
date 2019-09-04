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
typedef  int /*<<< orphan*/  mfxFrameSurface1 ;
struct TYPE_3__ {int /*<<< orphan*/ * dst; } ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_1__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int QSVDEINT_MORE_OUTPUT ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int process_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int submit_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int qsvdeint_filter_frame(AVFilterLink *link, AVFrame *in)
{
    AVFilterContext *ctx = link->dst;

    mfxFrameSurface1 *surf_in;
    int ret;

    ret = submit_frame(ctx, in, &surf_in);
    if (ret < 0) {
        av_frame_free(&in);
        return ret;
    }

    do {
        ret = process_frame(ctx, in, surf_in);
        if (ret < 0)
            return ret;
    } while (ret == QSVDEINT_MORE_OUTPUT);

    return 0;
}