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
struct TYPE_3__ {int /*<<< orphan*/  bitdepth; int /*<<< orphan*/  level; int /*<<< orphan*/  profile; } ;
typedef  TYPE_1__ VPCC ;
typedef  int /*<<< orphan*/  AVRational ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  AVCodecParameters ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_strlcatf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char*,int) ; 
 int ff_isom_get_vpcc_features (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void set_vp9_codec_str(AVFormatContext *s, AVCodecParameters *par,
                              AVRational *frame_rate, char *str, int size) {
    VPCC vpcc;
    int ret = ff_isom_get_vpcc_features(s, par, frame_rate, &vpcc);
    if (ret == 0) {
        av_strlcatf(str, size, "vp09.%02d.%02d.%02d",
                    vpcc.profile, vpcc.level, vpcc.bitdepth);
    } else {
        // Default to just vp9 in case of error while finding out profile or level
        av_log(s, AV_LOG_WARNING, "Could not find VP9 profile and/or level\n");
        av_strlcpy(str, "vp9", size);
    }
    return;
}