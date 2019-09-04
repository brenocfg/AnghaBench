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
 int AV_RB16 (int const*) ; 
 int FFMIN (int,int) ; 

__attribute__((used)) static int dvbsub_probe(const AVProbeData *p)
{
    int i, j, k;
    const uint8_t *end = p->buf + p->buf_size;
    int type, len;
    int max_score = 0;

    for(i=0; i<p->buf_size; i++){
        if (p->buf[i] == 0x0f) {
            const uint8_t *ptr = p->buf + i;
            uint8_t histogram[6] = {0};
            int min = 255;
            for(j=0; 6 < end - ptr; j++) {
                if (*ptr != 0x0f)
                    break;
                type    = ptr[1];
                //page_id = AV_RB16(ptr + 2);
                len     = AV_RB16(ptr + 4);
                if (type == 0x80) {
                    ;
                } else if (type >= 0x10 && type <= 0x14) {
                    histogram[type - 0x10] ++;
                } else
                    break;
                if (6 + len > end - ptr)
                    break;
                ptr += 6 + len;
            }
            for (k=0; k < 4; k++) {
                min = FFMIN(min, histogram[k]);
            }
            if (min && j > max_score)
                max_score = j;
        }
    }

    if (max_score > 5)
        return AVPROBE_SCORE_EXTENSION;

    return 0;
}