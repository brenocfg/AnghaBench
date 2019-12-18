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
struct TYPE_3__ {int buf_size; char* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RB16 (char*) ; 

__attribute__((used)) static int dxa_probe(const AVProbeData *p)
{
    int w, h;
    if (p->buf_size < 15)
        return 0;
    w = AV_RB16(p->buf + 11);
    h = AV_RB16(p->buf + 13);
    /* check file header */
    if (p->buf[0] == 'D' && p->buf[1] == 'E' &&
        p->buf[2] == 'X' && p->buf[3] == 'A' &&
        w && w <= 2048 && h && h <= 2048)
        return AVPROBE_SCORE_MAX;
    else
        return 0;
}