#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_12__ {scalar_t__ type; int w; char* h; TYPE_4__* dst; TYPE_2__* src; int /*<<< orphan*/  format; scalar_t__ sample_rate; int /*<<< orphan*/  channel_layout; } ;
struct TYPE_11__ {TYPE_3__* filter; } ;
struct TYPE_10__ {char* name; } ;
struct TYPE_9__ {TYPE_1__* filter; } ;
struct TYPE_8__ {char* name; } ;
typedef  TYPE_5__ AVFilterLink ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  av_get_channel_layout_string (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_get_sample_fmt_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_tlog (void*,char*,TYPE_5__*,int,char*,int /*<<< orphan*/ ,char*,char*,char*) ; 

void ff_tlog_link(void *ctx, AVFilterLink *link, int end)
{
    if (link->type == AVMEDIA_TYPE_VIDEO) {
        ff_tlog(ctx,
                "link[%p s:%dx%d fmt:%s %s->%s]%s",
                link, link->w, link->h,
                av_get_pix_fmt_name(link->format),
                link->src ? link->src->filter->name : "",
                link->dst ? link->dst->filter->name : "",
                end ? "\n" : "");
    } else {
        char buf[128];
        av_get_channel_layout_string(buf, sizeof(buf), -1, link->channel_layout);

        ff_tlog(ctx,
                "link[%p r:%d cl:%s fmt:%s %s->%s]%s",
                link, (int)link->sample_rate, buf,
                av_get_sample_fmt_name(link->format),
                link->src ? link->src->filter->name : "",
                link->dst ? link->dst->filter->name : "",
                end ? "\n" : "");
    }
}