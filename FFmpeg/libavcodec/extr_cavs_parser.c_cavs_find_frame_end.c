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
struct TYPE_3__ {int frame_start_found; int state; } ;
typedef  TYPE_1__ ParseContext ;

/* Variables and functions */
 int END_NOT_FOUND ; 
 int PIC_I_START_CODE ; 
 int PIC_PB_START_CODE ; 
 int SLICE_MAX_START_CODE ; 

__attribute__((used)) static int cavs_find_frame_end(ParseContext *pc, const uint8_t *buf,
                               int buf_size) {
    int pic_found, i;
    uint32_t state;

    pic_found= pc->frame_start_found;
    state= pc->state;

    i=0;
    if(!pic_found){
        for(i=0; i<buf_size; i++){
            state= (state<<8) | buf[i];
            if(state == PIC_I_START_CODE || state == PIC_PB_START_CODE){
                i++;
                pic_found=1;
                break;
            }
        }
    }

    if(pic_found){
        /* EOF considered as end of frame */
        if (buf_size == 0)
            return 0;
        for(; i<buf_size; i++){
            state= (state<<8) | buf[i];
            if((state&0xFFFFFF00) == 0x100){
                if(state > SLICE_MAX_START_CODE){
                    pc->frame_start_found=0;
                    pc->state=-1;
                    return i-3;
                }
            }
        }
    }
    pc->frame_start_found= pic_found;
    pc->state= state;
    return END_NOT_FOUND;
}