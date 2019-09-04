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
struct TYPE_3__ {int buf_size; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int AV_RB16 (int /*<<< orphan*/ *) ; 
 int AV_RB64 (int /*<<< orphan*/ *) ; 
 size_t FFMAX (int,int /*<<< orphan*/ ) ; 
 int av_log2_16bit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int h261_probe(const AVProbeData *p)
{
    int i;
    int valid_psc=0;
    int invalid_psc=0;
    int next_gn=0;
    int src_fmt=0;

    for(i=0; i<p->buf_size; i++){
        if ((AV_RB16(&p->buf[i]) - 1) < 0xFFU) {
            int shift = av_log2_16bit(p->buf[i+1]);
            uint32_t code = AV_RB64(&p->buf[FFMAX(i-1, 0)]) >> (24+shift);
            if ((code & 0xffff0000) == 0x10000) {
                int gn= (code>>12)&0xf;
                if(!gn)
                    src_fmt= code&8;
                if(gn != next_gn) invalid_psc++;
                else              valid_psc++;

                if(src_fmt){ // CIF
                    static const int lut[16]={1,2,3,4,5,6,7,8,9,10,11,12,0,16,16,16};
                    next_gn = lut[gn];
                }else{       //QCIF
                    static const int lut[16]={1,3,16,5,16,0,16,16,16,16,16,16,16,16,16,16};
                    next_gn = lut[gn];
                }
            }
        }
    }
    if(valid_psc > 2*invalid_psc + 6){
        return AVPROBE_SCORE_EXTENSION;
    }else if(valid_psc > 2*invalid_psc + 2)
        return AVPROBE_SCORE_EXTENSION / 2;
    return 0;
}