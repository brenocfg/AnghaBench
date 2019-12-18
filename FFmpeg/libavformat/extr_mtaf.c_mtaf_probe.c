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
struct TYPE_3__ {int buf_size; scalar_t__ buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ AV_RL32 (scalar_t__) ; 
 scalar_t__ MKTAG (char,char,char,char) ; 

__attribute__((used)) static int mtaf_probe(const AVProbeData *p)
{
    if (p->buf_size < 0x44)
        return 0;

    if (AV_RL32(p->buf) != MKTAG('M','T','A','F') ||
        AV_RL32(p->buf + 0x40) != MKTAG('H','E','A','D'))
        return 0;

    return AVPROBE_SCORE_MAX;
}