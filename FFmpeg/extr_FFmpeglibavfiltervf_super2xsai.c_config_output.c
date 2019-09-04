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
struct TYPE_5__ {int w; int h; int /*<<< orphan*/  format; int /*<<< orphan*/  dst; TYPE_1__* src; } ;
struct TYPE_4__ {TYPE_2__** inputs; } ;
typedef  TYPE_2__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterLink *inlink = outlink->src->inputs[0];

    outlink->w = inlink->w*2;
    outlink->h = inlink->h*2;

    av_log(inlink->dst, AV_LOG_VERBOSE, "fmt:%s size:%dx%d -> size:%dx%d\n",
           av_get_pix_fmt_name(inlink->format),
           inlink->w, inlink->h, outlink->w, outlink->h);

    return 0;
}