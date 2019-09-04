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
struct TYPE_3__ {int state; int frame_start_found; } ;
typedef  TYPE_1__ ParseContext ;
typedef  int /*<<< orphan*/  AVCodecParserContext ;

/* Variables and functions */
 int END_NOT_FOUND ; 
 int EXT_START_CODE ; 
 int PICTURE_START_CODE ; 
 int SEQ_END_CODE ; 
 int SEQ_START_CODE ; 
 int SLICE_MAX_START_CODE ; 
 int SLICE_MIN_START_CODE ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int const* avpriv_find_start_code (int const*,int const*,int*) ; 
 int /*<<< orphan*/  ff_fetch_timestamp (int /*<<< orphan*/ *,int,int,int) ; 

int ff_mpeg1_find_frame_end(ParseContext *pc, const uint8_t *buf, int buf_size, AVCodecParserContext *s)
{
    int i;
    uint32_t state = pc->state;

    /* EOF considered as end of frame */
    if (buf_size == 0)
        return 0;

/*
 0  frame start         -> 1/4
 1  first_SEQEXT        -> 0/2
 2  first field start   -> 3/0
 3  second_SEQEXT       -> 2/0
 4  searching end
*/

    for (i = 0; i < buf_size; i++) {
        av_assert1(pc->frame_start_found >= 0 && pc->frame_start_found <= 4);
        if (pc->frame_start_found & 1) {
            if (state == EXT_START_CODE && (buf[i] & 0xF0) != 0x80)
                pc->frame_start_found--;
            else if (state == EXT_START_CODE + 2) {
                if ((buf[i] & 3) == 3)
                    pc->frame_start_found = 0;
                else
                    pc->frame_start_found = (pc->frame_start_found + 1) & 3;
            }
            state++;
        } else {
            i = avpriv_find_start_code(buf + i, buf + buf_size, &state) - buf - 1;
            if (pc->frame_start_found == 0 && state >= SLICE_MIN_START_CODE && state <= SLICE_MAX_START_CODE) {
                i++;
                pc->frame_start_found = 4;
            }
            if (state == SEQ_END_CODE) {
                pc->frame_start_found = 0;
                pc->state=-1;
                return i+1;
            }
            if (pc->frame_start_found == 2 && state == SEQ_START_CODE)
                pc->frame_start_found = 0;
            if (pc->frame_start_found  < 4 && state == EXT_START_CODE)
                pc->frame_start_found++;
            if (pc->frame_start_found == 4 && (state & 0xFFFFFF00) == 0x100) {
                if (state < SLICE_MIN_START_CODE || state > SLICE_MAX_START_CODE) {
                    pc->frame_start_found = 0;
                    pc->state             = -1;
                    return i - 3;
                }
            }
            if (pc->frame_start_found == 0 && s && state == PICTURE_START_CODE) {
                ff_fetch_timestamp(s, i - 3, 1, i > 3);
            }
        }
    }
    pc->state = state;
    return END_NOT_FOUND;
}