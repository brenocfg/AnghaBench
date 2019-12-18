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
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int END_NOT_FOUND ; 

__attribute__((used)) static int h261_find_frame_end(ParseContext *pc, AVCodecContext *avctx,
                               const uint8_t *buf, int buf_size)
{
    int vop_found, i, j;
    uint32_t state;

    vop_found = pc->frame_start_found;
    state     = pc->state;

    for (i = 0; i < buf_size && !vop_found; i++) {
        state = (state << 8) | buf[i];
        for (j = 0; j < 8; j++) {
            if (((state >> j) & 0xFFFFF0) == 0x000100) {
                vop_found = 1;
                break;
            }
        }
    }
    if (vop_found) {
        for (; i < buf_size; i++) {
            state = (state << 8) | buf[i];
            for (j = 0; j < 8; j++) {
                if (((state >> j) & 0xFFFFF0) == 0x000100) {
                    pc->frame_start_found = 0;
                    pc->state             = (state >> (3 * 8)) + 0xFF00;
                    return i - 2;
                }
            }
        }
    }

    pc->frame_start_found = vop_found;
    pc->state             = state;
    return END_NOT_FOUND;
}