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
typedef  int uint64_t ;
struct TYPE_3__ {int buf_size; int* buf; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 

__attribute__((used)) static int h263_probe(const AVProbeData *p)
{
    uint64_t code= -1;
    int i;
    int valid_psc=0;
    int invalid_psc=0;
    int res_change=0;
    int src_fmt, last_src_fmt=-1;
    int last_gn=0;
    int tr, last_tr = -1;

    for(i=0; i<p->buf_size; i++){
        code = (code<<8) + p->buf[i];
        if ((code & 0xfffffc000000) == 0x80000000) {
            tr = (code >> 18) & 0xFF;
            src_fmt= (code>>10)&7;
            if(   src_fmt != last_src_fmt
               && last_src_fmt>0 && last_src_fmt<6
               && src_fmt<6)
                res_change++;

            if (tr == last_tr) {
                invalid_psc++;
                continue;
            }

            if (src_fmt != 7 && !(code&(1<<9)) && (code&(1<<5))) {
                invalid_psc++;
                continue;
            }

            if((code&0x30000)==0x20000 && src_fmt){
                valid_psc++;
                last_gn=0;
            }else
                invalid_psc++;
            last_src_fmt= src_fmt;
            last_tr = tr;
        } else if((code & 0xffff80000000) == 0x80000000) {
            int gn= (code>>(31-5)) & 0x1F;
            if(gn<last_gn){
                invalid_psc++;
            }else
                last_gn= gn;
        }
    }
    if(valid_psc > 2*invalid_psc + 2*res_change + 3){
        return AVPROBE_SCORE_EXTENSION;
    }else if(valid_psc > 2*invalid_psc)
        return AVPROBE_SCORE_EXTENSION / 2;
    return 0;
}