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
 int ff_subtitles_next_line (char const*) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 

__attribute__((used)) static int mpsub_probe(const AVProbeData *p)
{
    const char *ptr     = p->buf;
    const char *ptr_end = p->buf + p->buf_size;

    while (ptr < ptr_end) {
        int inc;

        if (!memcmp(ptr, "FORMAT=TIME", 11))
            return AVPROBE_SCORE_EXTENSION;
        if (!memcmp(ptr, "FORMAT=", 7))
            return AVPROBE_SCORE_EXTENSION / 3;
        inc = ff_subtitles_next_line(ptr);
        if (!inc)
            break;
        ptr += inc;
    }
    return 0;
}