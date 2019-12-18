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
typedef  int uint32_t ;
struct TYPE_3__ {int* buf; int buf_size; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_RB32 (int*) ; 
 int /*<<< orphan*/  ISAVS2 (int const) ; 
 scalar_t__ ISEND (int) ; 
 scalar_t__ ISPIC (int) ; 
 scalar_t__ ISSQH (int) ; 
 scalar_t__ ISUNIT (int) ; 
 int* avpriv_find_start_code (int const*,int const*,int*) ; 

__attribute__((used)) static int avs2_probe(const AVProbeData *p)
{
    uint32_t code= -1, hds=0, pic=0, seq=0;
    uint8_t state=0;
    const uint8_t *ptr = p->buf, *end = p->buf + p->buf_size, *sqb=0;
    if (AV_RB32(p->buf) != 0x1B0){
        return 0;
    }

    while (ptr < end) {
        ptr = avpriv_find_start_code(ptr, end, &code);
        state = code & 0xFF;
        if ((code & 0xffffff00) == 0x100) {
            if (ISUNIT(state)) {
                if (sqb && !hds) {
                    hds = ptr - sqb;
                }
                if (ISSQH(state)) {
                    if (!ISAVS2(*ptr))
                        return 0;
                    sqb = ptr;
                    seq++;
                } else if (ISPIC(state)) {
                    pic++;
                } else if (ISEND(state)) {
                    break;
                }
            }
        }
    }
    if (seq && hds >= 21 && pic){
        return AVPROBE_SCORE_EXTENSION + 2; // more than cavs
    }

    return 0;
}