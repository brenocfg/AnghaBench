#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  pad_idx; TYPE_1__* filter_ctx; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; int /*<<< orphan*/  ost; } ;
struct TYPE_10__ {int /*<<< orphan*/  output_pads; } ;
typedef  TYPE_2__ OutputFilter ;
typedef  int /*<<< orphan*/  FilterGraph ;
typedef  TYPE_3__ AVFilterInOut ;

/* Variables and functions */
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int avfilter_pad_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int configure_output_audio_filter (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 int configure_output_video_filter (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  exit_program (int) ; 

int configure_output_filter(FilterGraph *fg, OutputFilter *ofilter, AVFilterInOut *out)
{
    if (!ofilter->ost) {
        av_log(NULL, AV_LOG_FATAL, "Filter %s has an unconnected output\n", ofilter->name);
        exit_program(1);
    }

    switch (avfilter_pad_get_type(out->filter_ctx->output_pads, out->pad_idx)) {
    case AVMEDIA_TYPE_VIDEO: return configure_output_video_filter(fg, ofilter, out);
    case AVMEDIA_TYPE_AUDIO: return configure_output_audio_filter(fg, ofilter, out);
    default: av_assert0(0);
    }
}