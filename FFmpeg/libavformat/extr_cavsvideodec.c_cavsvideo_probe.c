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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {scalar_t__* buf; int buf_size; } ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int CAVS_PIC_I_START_CODE ; 
 int CAVS_PIC_PB_START_CODE ; 
 scalar_t__ const CAVS_PROFILE_JIZHUN ; 
 int CAVS_SEQ_START_CODE ; 
 int CAVS_UNDEF_START_CODE ; 
 int CAVS_VIDEO_EDIT_CODE ; 
 scalar_t__* avpriv_find_start_code (scalar_t__ const*,scalar_t__ const*,int*) ; 

__attribute__((used)) static int cavsvideo_probe(const AVProbeData *p)
{
    uint32_t code= -1;
    int pic=0, seq=0, slice_pos = 0;
    const uint8_t *ptr = p->buf, *end = p->buf + p->buf_size;

    while (ptr < end) {
        ptr = avpriv_find_start_code(ptr, end, &code);
        if ((code & 0xffffff00) == 0x100) {
            if(code < CAVS_SEQ_START_CODE) {
                /* slices have to be consecutive */
                if(code < slice_pos)
                    return 0;
                slice_pos = code;
            } else {
                slice_pos = 0;
            }
            if (code == CAVS_SEQ_START_CODE) {
                seq++;
                /* check for the only currently supported profile */
                if (*ptr != CAVS_PROFILE_JIZHUN)
                    return 0;
            } else if ((code == CAVS_PIC_I_START_CODE) ||
                       (code == CAVS_PIC_PB_START_CODE)) {
                pic++;
            } else if ((code == CAVS_UNDEF_START_CODE) ||
                       (code >  CAVS_VIDEO_EDIT_CODE)) {
                return 0;
            }
        }
    }
    if(seq && seq*9<=pic*10)
        return AVPROBE_SCORE_EXTENSION+1;
    return 0;
}