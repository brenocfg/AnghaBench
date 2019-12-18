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
typedef  float uint8_t ;
struct TYPE_3__ {float* buf; unsigned int buf_size; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 unsigned int AV_RB32 (float const*) ; 
 int /*<<< orphan*/  memcmp (float const*,char*,int) ; 

__attribute__((used)) static int probe(const AVProbeData *p, int live)
{
    const uint8_t *d = p->buf;
    unsigned offset = AV_RB32(d + 5);

    if (d[0] == 'F' &&
        d[1] == 'L' &&
        d[2] == 'V' &&
        d[3] < 5 && d[5] == 0 &&
        offset + 100 < p->buf_size &&
        offset > 8) {
        int is_live = !memcmp(d + offset + 40, "NGINX RTMP", 10);

        if (live == is_live)
            return AVPROBE_SCORE_MAX;
    }
    return 0;
}