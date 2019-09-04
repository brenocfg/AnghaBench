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
 scalar_t__ ISUNIT (int const) ; 
 int SLICE_MAX_START_CODE ; 

__attribute__((used)) static int avs2_find_frame_end(ParseContext *pc, const uint8_t *buf, int buf_size)
{
    int pic_found  = pc->frame_start_found;
    uint32_t state = pc->state;
    int cur = 0;

    if (!pic_found) {
        for (; cur < buf_size; ++cur) {
            state = (state<<8) | buf[cur];
            if (ISUNIT(buf[cur])){
                ++cur;
                pic_found = 1;
                break;
            }
        }
    }

    if (pic_found) {
        if (!buf_size)
            return END_NOT_FOUND;
        for (; cur < buf_size; ++cur) {
            state = (state << 8) | buf[cur];
            if ((state & 0xFFFFFF00) == 0x100 && state > SLICE_MAX_START_CODE) {
                pc->frame_start_found = 0;
                pc->state = -1;
                return cur - 3;
            }
        }
    }

    pc->frame_start_found = pic_found;
    pc->state = state;

    return END_NOT_FOUND;
}