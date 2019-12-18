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
struct TYPE_3__ {int* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 

__attribute__((used)) static int probe(const AVProbeData *p)
{
    // the single file I have starts with that, I do not know if others do, too
    if(   p->buf[0] == 1
       && p->buf[1] == 1
       && p->buf[2] == 3
       && p->buf[3] == 0xB8
       && p->buf[4] == 0x80
       && p->buf[5] == 0x60
      )
        return AVPROBE_SCORE_MAX-2;

    return 0;
}