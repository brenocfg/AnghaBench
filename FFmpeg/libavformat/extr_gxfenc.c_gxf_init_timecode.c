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
struct TYPE_3__ {int ff; int drop; scalar_t__ color; int /*<<< orphan*/  ss; int /*<<< orphan*/  mm; int /*<<< orphan*/  hh; } ;
typedef  TYPE_1__ GXFTimecode ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int*) ; 

__attribute__((used)) static int gxf_init_timecode(AVFormatContext *s, GXFTimecode *tc, const char *tcstr, int fields)
{
    char c;

    if (sscanf(tcstr, "%d:%d:%d%c%d", &tc->hh, &tc->mm, &tc->ss, &c, &tc->ff) != 5) {
        av_log(s, AV_LOG_ERROR, "unable to parse timecode, "
                                "syntax: hh:mm:ss[:;.]ff\n");
        return -1;
    }

    tc->color = 0;
    tc->drop = c != ':';

    if (fields == 2)
        tc->ff = tc->ff * 2;

    return 0;
}