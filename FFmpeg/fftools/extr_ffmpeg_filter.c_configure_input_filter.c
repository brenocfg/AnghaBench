#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  pad_idx; TYPE_3__* filter_ctx; } ;
struct TYPE_15__ {TYPE_2__* ist; } ;
struct TYPE_14__ {int /*<<< orphan*/  input_pads; } ;
struct TYPE_13__ {TYPE_1__* st; int /*<<< orphan*/  file_index; int /*<<< orphan*/  dec; } ;
struct TYPE_12__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_4__ InputFilter ;
typedef  int /*<<< orphan*/  FilterGraph ;
typedef  TYPE_5__ AVFilterInOut ;

/* Variables and functions */
 int AVERROR_DECODER_NOT_FOUND ; 
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avfilter_pad_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int configure_input_audio_filter (int /*<<< orphan*/ *,TYPE_4__*,TYPE_5__*) ; 
 int configure_input_video_filter (int /*<<< orphan*/ *,TYPE_4__*,TYPE_5__*) ; 

__attribute__((used)) static int configure_input_filter(FilterGraph *fg, InputFilter *ifilter,
                                  AVFilterInOut *in)
{
    if (!ifilter->ist->dec) {
        av_log(NULL, AV_LOG_ERROR,
               "No decoder for stream #%d:%d, filtering impossible\n",
               ifilter->ist->file_index, ifilter->ist->st->index);
        return AVERROR_DECODER_NOT_FOUND;
    }
    switch (avfilter_pad_get_type(in->filter_ctx->input_pads, in->pad_idx)) {
    case AVMEDIA_TYPE_VIDEO: return configure_input_video_filter(fg, ifilter, in);
    case AVMEDIA_TYPE_AUDIO: return configure_input_audio_filter(fg, ifilter, in);
    default: av_assert0(0);
    }
}