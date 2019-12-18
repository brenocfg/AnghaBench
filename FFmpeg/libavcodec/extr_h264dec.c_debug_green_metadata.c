#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {float green_metadata_type; float period_type; float num_seconds; float num_pictures; float xsd_metric_type; scalar_t__ xsd_metric_value; scalar_t__ percent_alpha_point_deblocking_instance; scalar_t__ percent_six_tap_filtering; scalar_t__ percent_intra_coded_macroblocks; scalar_t__ percent_non_zero_macroblocks; } ;
typedef  TYPE_1__ H264SEIGreenMetaData ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void debug_green_metadata(const H264SEIGreenMetaData *gm, void *logctx)
{
    av_log(logctx, AV_LOG_DEBUG, "Green Metadata Info SEI message\n");
    av_log(logctx, AV_LOG_DEBUG, "  green_metadata_type: %d\n", gm->green_metadata_type);

    if (gm->green_metadata_type == 0) {
        av_log(logctx, AV_LOG_DEBUG, "  green_metadata_period_type: %d\n", gm->period_type);

        if (gm->period_type == 2)
            av_log(logctx, AV_LOG_DEBUG, "  green_metadata_num_seconds: %d\n", gm->num_seconds);
        else if (gm->period_type == 3)
            av_log(logctx, AV_LOG_DEBUG, "  green_metadata_num_pictures: %d\n", gm->num_pictures);

        av_log(logctx, AV_LOG_DEBUG, "  SEI GREEN Complexity Metrics: %f %f %f %f\n",
               (float)gm->percent_non_zero_macroblocks/255,
               (float)gm->percent_intra_coded_macroblocks/255,
               (float)gm->percent_six_tap_filtering/255,
               (float)gm->percent_alpha_point_deblocking_instance/255);

    } else if (gm->green_metadata_type == 1) {
        av_log(logctx, AV_LOG_DEBUG, "  xsd_metric_type: %d\n", gm->xsd_metric_type);

        if (gm->xsd_metric_type == 0)
            av_log(logctx, AV_LOG_DEBUG, "  xsd_metric_value: %f\n",
                   (float)gm->xsd_metric_value/100);
    }
}