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
struct TYPE_8__ {TYPE_1__* dstpad; } ;
struct TYPE_7__ {int /*<<< orphan*/ * (* get_video_buffer ) (TYPE_2__*,int,int) ;} ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  FF_TPRINTF_START (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_default_get_video_buffer (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  ff_tlog_link (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_video_buffer ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,int,int) ; 

AVFrame *ff_get_video_buffer(AVFilterLink *link, int w, int h)
{
    AVFrame *ret = NULL;

    FF_TPRINTF_START(NULL, get_video_buffer); ff_tlog_link(NULL, link, 0);

    if (link->dstpad->get_video_buffer)
        ret = link->dstpad->get_video_buffer(link, w, h);

    if (!ret)
        ret = ff_default_get_video_buffer(link, w, h);

    return ret;
}