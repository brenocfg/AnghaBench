#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_9__ {int width; } ;
struct TYPE_8__ {TYPE_2__* last_frame; } ;
typedef  TYPE_1__ IpvideoContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  copy_from (TYPE_1__*,TYPE_2__*,TYPE_2__*,int,int) ; 

__attribute__((used)) static void ipvideo_format_06_secondpass(IpvideoContext *s, AVFrame *frame, int16_t opcode)
{
    int off_x, off_y;

    if (opcode < 0) {
        off_x = ((uint16_t)opcode - 0xC000) % frame->width;
        off_y = ((uint16_t)opcode - 0xC000) / frame->width;
        copy_from(s, s->last_frame, frame, off_x, off_y);
    } else if (opcode > 0) {
        off_x = ((uint16_t)opcode - 0x4000) % frame->width;
        off_y = ((uint16_t)opcode - 0x4000) / frame->width;
        copy_from(s, frame, frame, off_x, off_y);
    }
}