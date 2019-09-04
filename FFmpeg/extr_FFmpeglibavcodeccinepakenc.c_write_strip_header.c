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
struct TYPE_3__ {int w; } ;
typedef  TYPE_1__ CinepakEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WB16 (unsigned char*,int) ; 
 int /*<<< orphan*/  AV_WB24 (unsigned char*,scalar_t__) ; 
 scalar_t__ STRIP_HEADER_SIZE ; 

__attribute__((used)) static void write_strip_header(CinepakEncContext *s, int y, int h, int keyframe,
                               unsigned char *buf, int strip_size)
{
    // actually we are exclusively using intra strip coding (how much can we win
    // otherwise? how to choose which part of a codebook to update?),
    // keyframes are different only because we disallow ENC_SKIP on them -- rl
    // (besides, the logic here used to be inverted: )
    //    buf[0] = keyframe ? 0x11: 0x10;
    buf[0] = keyframe ? 0x10 : 0x11;
    AV_WB24(&buf[1], strip_size + STRIP_HEADER_SIZE);
    // AV_WB16(&buf[4], y); /* using absolute y values works -- rl */
    AV_WB16(&buf[4], 0); /* using relative values works as well -- rl */
    AV_WB16(&buf[6], 0);
    // AV_WB16(&buf[8], y + h); /* using absolute y values works -- rl */
    AV_WB16(&buf[8], h); /* using relative values works as well -- rl */
    AV_WB16(&buf[10], s->w);
}