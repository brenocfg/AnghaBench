#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mb_info; int prev_mb_info; int last_mb_info; scalar_t__ mb_info_size; int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int put_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_mb_info (TYPE_1__*) ; 

__attribute__((used)) static void update_mb_info(MpegEncContext *s, int startcode)
{
    if (!s->mb_info)
        return;
    if (put_bits_count(&s->pb) - s->prev_mb_info*8 >= s->mb_info*8) {
        s->mb_info_size += 12;
        s->prev_mb_info = s->last_mb_info;
    }
    if (startcode) {
        s->prev_mb_info = put_bits_count(&s->pb)/8;
        /* This might have incremented mb_info_size above, and we return without
         * actually writing any info into that slot yet. But in that case,
         * this will be called again at the start of the after writing the
         * start code, actually writing the mb info. */
        return;
    }

    s->last_mb_info = put_bits_count(&s->pb)/8;
    if (!s->mb_info_size)
        s->mb_info_size += 12;
    write_mb_info(s);
}