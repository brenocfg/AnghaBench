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
struct TYPE_3__ {size_t data_stack_top; int /*<<< orphan*/ ** line; int /*<<< orphan*/ ** data_stack; } ;
typedef  TYPE_1__ slice_buffer ;
typedef  int /*<<< orphan*/  IDWTELEM ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 

IDWTELEM *ff_slice_buffer_load_line(slice_buffer *buf, int line)
{
    IDWTELEM *buffer;

    av_assert0(buf->data_stack_top >= 0);
//  av_assert1(!buf->line[line]);
    if (buf->line[line])
        return buf->line[line];

    buffer = buf->data_stack[buf->data_stack_top];
    buf->data_stack_top--;
    buf->line[line] = buffer;

    return buffer;
}