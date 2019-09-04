#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_5__* avctx; } ;
typedef  TYPE_1__ V4L2m2mContext ;
struct TYPE_8__ {scalar_t__ max_b_frames; } ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  B_FRAMES ; 
 int /*<<< orphan*/  MPEG_CID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  v4l2_get_ext_ctrl (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,char*) ; 
 int /*<<< orphan*/  v4l2_set_ext_ctrl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int v4l2_check_b_frame_support(V4L2m2mContext *s)
{
    if (s->avctx->max_b_frames)
        av_log(s->avctx, AV_LOG_WARNING, "Encoder does not support b-frames yet\n");

    v4l2_set_ext_ctrl(s, MPEG_CID(B_FRAMES), 0, "number of B-frames");
    v4l2_get_ext_ctrl(s, MPEG_CID(B_FRAMES), &s->avctx->max_b_frames, "number of B-frames");
    if (s->avctx->max_b_frames == 0)
        return 0;

    avpriv_report_missing_feature(s->avctx, "DTS/PTS calculation for V4L2 encoding");

    return AVERROR_PATCHWELCOME;
}