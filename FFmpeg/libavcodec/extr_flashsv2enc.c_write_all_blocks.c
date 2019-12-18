#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {scalar_t__ dirty; scalar_t__ len; scalar_t__ start; } ;
struct TYPE_5__ {int rows; int cols; TYPE_2__* frame_blocks; } ;
typedef  TYPE_1__ FlashSV2Context ;
typedef  TYPE_2__ Block ;

/* Variables and functions */
 int write_block (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int write_all_blocks(FlashSV2Context * s, uint8_t * buf,
                            int buf_size)
{
    int row, col, buf_pos = 0, len;
    Block *b;
    for (row = 0; row < s->rows; row++) {
        for (col = 0; col < s->cols; col++) {
            b = s->frame_blocks + row * s->cols + col;
            len = write_block(b, buf + buf_pos, buf_size - buf_pos);
            b->start = b->len = b->dirty = 0;
            if (len < 0)
                return len;
            buf_pos += len;
        }
    }
    return buf_pos;
}