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
typedef  int uint32_t ;
struct TYPE_3__ {int buf_size; int* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_RL32 (int*) ; 

__attribute__((used)) static int vc1t_probe(const AVProbeData *p)
{
    uint32_t size;

    if (p->buf_size < 24)
        return 0;

    size = AV_RL32(&p->buf[4]);
    if (p->buf[3] != 0xC5 || size < 4 || size > p->buf_size - 20 ||
        AV_RL32(&p->buf[size+16]) != 0xC)
        return 0;

    return AVPROBE_SCORE_EXTENSION;
}