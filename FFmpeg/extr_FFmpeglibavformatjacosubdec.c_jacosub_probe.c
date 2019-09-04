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
struct TYPE_3__ {char* buf; int buf_size; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_RB24 (char const*) ; 
 int /*<<< orphan*/  ff_subtitles_next_line (char const*) ; 
 scalar_t__ jss_whitespace (char const) ; 
 scalar_t__ timed_line (char const*) ; 

__attribute__((used)) static int jacosub_probe(const AVProbeData *p)
{
    const char *ptr     = p->buf;
    const char *ptr_end = p->buf + p->buf_size;

    if (AV_RB24(ptr) == 0xEFBBBF)
        ptr += 3; /* skip UTF-8 BOM */

    while (ptr < ptr_end) {
        while (jss_whitespace(*ptr))
            ptr++;
        if (*ptr != '#' && *ptr != '\n') {
            if (timed_line(ptr))
                return AVPROBE_SCORE_EXTENSION + 1;
            return 0;
        }
        ptr += ff_subtitles_next_line(ptr);
    }
    return 0;
}