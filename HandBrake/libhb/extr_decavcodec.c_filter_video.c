#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * graph; } ;
struct TYPE_7__ {int /*<<< orphan*/  nframes; int /*<<< orphan*/  frame; int /*<<< orphan*/  list; TYPE_1__ video_filters; } ;
typedef  TYPE_2__ hb_work_private_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * copy_frame (TYPE_2__*) ; 
 int /*<<< orphan*/  hb_avfilter_add_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hb_avfilter_get_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_video_filters (TYPE_2__*) ; 

__attribute__((used)) static void filter_video(hb_work_private_t *pv)
{
    reinit_video_filters(pv);
    if (pv->video_filters.graph != NULL)
    {
        int result;

        hb_avfilter_add_frame(pv->video_filters.graph, pv->frame);
        result = hb_avfilter_get_frame(pv->video_filters.graph, pv->frame);
        while (result >= 0)
        {
            hb_buffer_t * buf = copy_frame(pv);
            hb_buffer_list_append(&pv->list, buf);
            av_frame_unref(pv->frame);
            ++pv->nframes;
            result = hb_avfilter_get_frame(pv->video_filters.graph, pv->frame);
        }
    }
    else
    {
        hb_buffer_t * buf = copy_frame(pv);
        hb_buffer_list_append(&pv->list, buf);
        av_frame_unref(pv->frame);
        ++pv->nframes;
    }
}