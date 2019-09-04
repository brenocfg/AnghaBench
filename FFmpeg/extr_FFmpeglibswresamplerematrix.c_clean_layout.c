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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int AV_CH_FRONT_CENTER ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  av_get_channel_layout_string (char*,int,int,int) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int clean_layout(void *s, int64_t layout){
    if(layout && layout != AV_CH_FRONT_CENTER && !(layout&(layout-1))) {
        char buf[128];
        av_get_channel_layout_string(buf, sizeof(buf), -1, layout);
        av_log(s, AV_LOG_VERBOSE, "Treating %s as mono\n", buf);
        return AV_CH_FRONT_CENTER;
    }

    return layout;
}