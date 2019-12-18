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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  AVOption ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*) ; 
 int av_parse_color (int /*<<< orphan*/ *,char const*,int,void*) ; 

__attribute__((used)) static int set_string_color(void *obj, const AVOption *o, const char *val, uint8_t *dst)
{
    int ret;

    if (!val) {
        return 0;
    } else {
        ret = av_parse_color(dst, val, -1, obj);
        if (ret < 0)
            av_log(obj, AV_LOG_ERROR, "Unable to parse option value \"%s\" as color\n", val);
        return ret;
    }
    return 0;
}