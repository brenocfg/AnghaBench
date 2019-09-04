#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {double MaxCLL; } ;
struct TYPE_10__ {scalar_t__ color_trc; } ;
struct TYPE_9__ {scalar_t__ data; } ;
struct TYPE_8__ {int /*<<< orphan*/  max_luminance; scalar_t__ has_luminance; } ;
typedef  TYPE_1__ AVMasteringDisplayMetadata ;
typedef  TYPE_2__ AVFrameSideData ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVContentLightMetadata ;

/* Variables and functions */
 scalar_t__ AVCOL_TRC_SMPTE2084 ; 
 int /*<<< orphan*/  AV_FRAME_DATA_CONTENT_LIGHT_LEVEL ; 
 int /*<<< orphan*/  AV_FRAME_DATA_MASTERING_DISPLAY_METADATA ; 
 double REFERENCE_WHITE ; 
 TYPE_2__* av_frame_get_side_data (TYPE_3__*,int /*<<< orphan*/ ) ; 
 double av_q2d (int /*<<< orphan*/ ) ; 

double ff_determine_signal_peak(AVFrame *in)
{
    AVFrameSideData *sd = av_frame_get_side_data(in, AV_FRAME_DATA_CONTENT_LIGHT_LEVEL);
    double peak = 0;

    if (sd) {
        AVContentLightMetadata *clm = (AVContentLightMetadata *)sd->data;
        peak = clm->MaxCLL / REFERENCE_WHITE;
    }

    sd = av_frame_get_side_data(in, AV_FRAME_DATA_MASTERING_DISPLAY_METADATA);
    if (!peak && sd) {
        AVMasteringDisplayMetadata *metadata = (AVMasteringDisplayMetadata *)sd->data;
        if (metadata->has_luminance)
            peak = av_q2d(metadata->max_luminance) / REFERENCE_WHITE;
    }

    // For untagged source, use peak of 10000 if SMPTE ST.2084
    // otherwise assume HLG with reference display peak 1000.
    if (!peak)
        peak = in->color_trc == AVCOL_TRC_SMPTE2084 ? 100.0f : 10.0f;

    return peak;
}