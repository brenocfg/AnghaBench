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
struct TYPE_3__ {int buf_size; int* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_MAX ; 
 int AV_RL32 (int*) ; 

__attribute__((used)) static int aea_read_probe(const AVProbeData *p)
{
    if (p->buf_size <= 2048+212)
        return 0;

    /* Magic is '00 08 00 00' in little-endian*/
    if (AV_RL32(p->buf)==0x800) {
        int ch, i;
        ch = p->buf[264];

        if (ch != 1 && ch != 2)
            return 0;

        /* Check so that the redundant bsm bytes and info bytes are valid
         * the block size mode bytes have to be the same
         * the info bytes have to be the same
         */
        for (i = 2048; i + 211 < p->buf_size; i+= 212) {
            int bsm_s, bsm_e, inb_s, inb_e;
            bsm_s = p->buf[0];
            inb_s = p->buf[1];
            inb_e = p->buf[210];
            bsm_e = p->buf[211];

            if (bsm_s != bsm_e || inb_s != inb_e)
                return 0;
        }
        return AVPROBE_SCORE_MAX / 4 + 1;
    }
    return 0;
}