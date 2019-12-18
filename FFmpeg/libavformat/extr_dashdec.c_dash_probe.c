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
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ av_stristr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int dash_probe(const AVProbeData *p)
{
    if (!av_stristr(p->buf, "<MPD"))
        return 0;

    if (av_stristr(p->buf, "dash:profile:isoff-on-demand:2011") ||
        av_stristr(p->buf, "dash:profile:isoff-live:2011") ||
        av_stristr(p->buf, "dash:profile:isoff-live:2012") ||
        av_stristr(p->buf, "dash:profile:isoff-main:2011")) {
        return AVPROBE_SCORE_MAX;
    }
    if (av_stristr(p->buf, "dash:profile")) {
        return AVPROBE_SCORE_MAX;
    }

    return 0;
}