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
struct TYPE_3__ {unsigned char* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RB24 (unsigned char const*) ; 
 int /*<<< orphan*/  ff_subtitles_next_line (unsigned char const*) ; 
 int sscanf (unsigned char const*,char*,char*) ; 
 int /*<<< orphan*/  strncmp (unsigned char const*,char*,int) ; 

__attribute__((used)) static int stl_probe(const AVProbeData *p)
{
    char c;
    const unsigned char *ptr = p->buf;

    if (AV_RB24(ptr) == 0xEFBBBF)
        ptr += 3;  /* skip UTF-8 BOM */

    while (*ptr == '\r' || *ptr == '\n' || *ptr == '$' || !strncmp(ptr, "//" , 2))
        ptr += ff_subtitles_next_line(ptr);

    if (sscanf(ptr, "%*d:%*d:%*d:%*d , %*d:%*d:%*d:%*d , %c", &c) == 1)
        return AVPROBE_SCORE_MAX;

    return 0;
}