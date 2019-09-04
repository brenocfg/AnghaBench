#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* filter; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int avfilter_link (TYPE_2__*,int,TYPE_2__*,int) ; 

__attribute__((used)) static int link_filter(AVFilterContext *src, int srcpad,
                       AVFilterContext *dst, int dstpad,
                       void *log_ctx)
{
    int ret;
    if ((ret = avfilter_link(src, srcpad, dst, dstpad))) {
        av_log(log_ctx, AV_LOG_ERROR,
               "Cannot create the link %s:%d -> %s:%d\n",
               src->filter->name, srcpad, dst->filter->name, dstpad);
        return ret;
    }

    return 0;
}