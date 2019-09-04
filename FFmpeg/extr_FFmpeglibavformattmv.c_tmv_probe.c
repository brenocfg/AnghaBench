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
 scalar_t__ AV_RL16 (int*) ; 
 scalar_t__ AV_RL32 (int*) ; 
 scalar_t__ PROBE_MIN_AUDIO_SIZE ; 
 scalar_t__ PROBE_MIN_SAMPLE_RATE ; 
 scalar_t__ TMV_TAG ; 

__attribute__((used)) static int tmv_probe(const AVProbeData *p)
{
    if (AV_RL32(p->buf)   == TMV_TAG &&
        AV_RL16(p->buf+4) >= PROBE_MIN_SAMPLE_RATE &&
        AV_RL16(p->buf+6) >= PROBE_MIN_AUDIO_SIZE  &&
               !p->buf[8] && // compression method
                p->buf[9] && // char cols
                p->buf[10])  // char rows
        return AVPROBE_SCORE_MAX /
            ((p->buf[9] == 40 && p->buf[10] == 25) ? 1 : 4);
    return 0;
}