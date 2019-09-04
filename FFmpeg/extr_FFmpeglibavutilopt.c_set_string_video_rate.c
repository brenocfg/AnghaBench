#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVRational ;
typedef  int /*<<< orphan*/  AVOption ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*) ; 
 int av_parse_video_rate (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int set_string_video_rate(void *obj, const AVOption *o, const char *val, AVRational *dst)
{
    int ret;
    if (!val) {
        ret = AVERROR(EINVAL);
    } else {
        ret = av_parse_video_rate(dst, val);
    }
    if (ret < 0)
        av_log(obj, AV_LOG_ERROR, "Unable to parse option value \"%s\" as video rate\n", val);
    return ret;
}