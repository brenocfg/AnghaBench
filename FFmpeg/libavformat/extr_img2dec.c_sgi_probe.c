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
typedef  int uint8_t ;
struct TYPE_3__ {int* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_RB16 (int const*) ; 

__attribute__((used)) static int sgi_probe(const AVProbeData *p)
{
    const uint8_t *b = p->buf;

    if (AV_RB16(b) == 474 &&
        (b[2] & ~1) == 0 &&
        (b[3] & ~3) == 0 && b[3] &&
        (AV_RB16(b + 4) & ~7) == 0 && AV_RB16(b + 4))
        return AVPROBE_SCORE_EXTENSION + 1;
    return 0;
}