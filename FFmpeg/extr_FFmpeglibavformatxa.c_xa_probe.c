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
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_RL16 (scalar_t__) ; 
 int AV_RL32 (scalar_t__) ; 
#define  XA00_TAG 130 
#define  XAI0_TAG 129 
#define  XAJ0_TAG 128 

__attribute__((used)) static int xa_probe(const AVProbeData *p)
{
    int channels, srate, bits_per_sample;
    if (p->buf_size < 24)
        return 0;
    switch(AV_RL32(p->buf)) {
    case XA00_TAG:
    case XAI0_TAG:
    case XAJ0_TAG:
        break;
    default:
        return 0;
    }
    channels        = AV_RL16(p->buf + 10);
    srate           = AV_RL32(p->buf + 12);
    bits_per_sample = AV_RL16(p->buf + 22);
    if (!channels || channels > 8 || !srate || srate > 192000 ||
        bits_per_sample < 4 || bits_per_sample > 32)
        return 0;
    return AVPROBE_SCORE_EXTENSION;
}