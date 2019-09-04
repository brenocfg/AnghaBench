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
struct TYPE_3__ {char* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static int aqt_probe(const AVProbeData *p)
{
    int frame;
    const char *ptr = p->buf;

    if (sscanf(ptr, "-->> %d", &frame) == 1)
        return AVPROBE_SCORE_EXTENSION;
    return 0;
}