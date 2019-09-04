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
 int sscanf (unsigned char const*,char*,char*) ; 
 scalar_t__ strchr (char*,char) ; 

__attribute__((used)) static int vplayer_probe(const AVProbeData *p)
{
    char c;
    const unsigned char *ptr = p->buf;

    if ((sscanf(ptr, "%*3d:%*2d:%*2d.%*2d%c", &c) == 1 ||
         sscanf(ptr, "%*3d:%*2d:%*2d%c",      &c) == 1) && strchr(": =", c))
        return AVPROBE_SCORE_MAX;
    return 0;
}