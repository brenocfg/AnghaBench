#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ HLSContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int HLS_SECOND_LEVEL_SEGMENT_DURATION ; 
 int HLS_SECOND_LEVEL_SEGMENT_INDEX ; 
 int HLS_SECOND_LEVEL_SEGMENT_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sls_flag_check_duration_size_index(HLSContext *hls)
{
    int ret = 0;

    if (hls->flags & HLS_SECOND_LEVEL_SEGMENT_DURATION) {
        av_log(hls, AV_LOG_ERROR,
               "second_level_segment_duration hls_flag requires strftime to be true\n");
        ret = AVERROR(EINVAL);
    }
    if (hls->flags & HLS_SECOND_LEVEL_SEGMENT_SIZE) {
        av_log(hls, AV_LOG_ERROR,
               "second_level_segment_size hls_flag requires strfime to be true\n");
        ret = AVERROR(EINVAL);
    }
    if (hls->flags & HLS_SECOND_LEVEL_SEGMENT_INDEX) {
        av_log(hls, AV_LOG_ERROR,
               "second_level_segment_index hls_flag requires strftime to be true\n");
        ret = AVERROR(EINVAL);
    }

    return ret;
}