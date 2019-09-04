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
struct TYPE_3__ {int* buf; int buf_size; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 

__attribute__((used)) static int gsm_probe(const AVProbeData *p)
{
    int valid = 0, invalid = 0;
    uint8_t *b = p->buf;
    while (b < p->buf + p->buf_size - 32) {
        if ((*b & 0xf0) == 0xd0) {
            valid++;
        } else {
            invalid++;
        }
        b += 33;
    }
    if (valid >> 5 > invalid)
        return AVPROBE_SCORE_EXTENSION + 1;
    return 0;
}