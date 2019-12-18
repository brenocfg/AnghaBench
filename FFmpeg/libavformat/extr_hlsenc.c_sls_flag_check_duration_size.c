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
struct TYPE_6__ {int /*<<< orphan*/  basename; } ;
typedef  TYPE_1__ VariantStream ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_2__ HLSContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int HLS_SECOND_LEVEL_SEGMENT_DURATION ; 
 int HLS_SECOND_LEVEL_SEGMENT_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 char* avio_find_protocol_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int sls_flag_check_duration_size(HLSContext *hls, VariantStream *vs)
{
    const char *proto = avio_find_protocol_name(vs->basename);
    int segment_renaming_ok = proto && !strcmp(proto, "file");
    int ret = 0;

    if ((hls->flags & HLS_SECOND_LEVEL_SEGMENT_DURATION) && !segment_renaming_ok) {
        av_log(hls, AV_LOG_ERROR,
               "second_level_segment_duration hls_flag works only with file protocol segment names\n");
        ret = AVERROR(EINVAL);
    }
    if ((hls->flags & HLS_SECOND_LEVEL_SEGMENT_SIZE) && !segment_renaming_ok) {
        av_log(hls, AV_LOG_ERROR,
               "second_level_segment_size hls_flag works only with file protocol segment names\n");
        ret = AVERROR(EINVAL);
    }

    return ret;
}