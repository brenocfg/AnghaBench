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
struct TYPE_4__ {int /*<<< orphan*/ * src; } ;
typedef  TYPE_1__ AVFilterLink ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 unsigned int FF_OUTLINK_IDX (TYPE_1__*) ; 
 int movie_push_frame (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int movie_request_frame(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    unsigned out_id = FF_OUTLINK_IDX(outlink);
    int ret;

    while (1) {
        ret = movie_push_frame(ctx, out_id);
        if (ret)
            return FFMIN(ret, 0);
    }
}