#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_7__ {int width; } ;
struct TYPE_6__ {TYPE_4__* cur_decode_frame; TYPE_4__* prev_decode_frame; } ;
typedef  TYPE_1__ IpvideoContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  copy_from (TYPE_1__*,TYPE_4__*,TYPE_4__*,int,int) ; 

__attribute__((used)) static void ipvideo_format_10_secondpass(IpvideoContext *s, AVFrame *frame, int16_t opcode)
{
    int off_x, off_y;

    if (opcode < 0) {
        off_x = ((uint16_t)opcode - 0xC000) % s->cur_decode_frame->width;
        off_y = ((uint16_t)opcode - 0xC000) / s->cur_decode_frame->width;
        copy_from(s, s->prev_decode_frame, s->cur_decode_frame, off_x, off_y);
    } else if (opcode > 0) {
        off_x = ((uint16_t)opcode - 0x4000) % s->cur_decode_frame->width;
        off_y = ((uint16_t)opcode - 0x4000) / s->cur_decode_frame->width;
        copy_from(s, s->cur_decode_frame, s->cur_decode_frame, off_x, off_y);
    }
}