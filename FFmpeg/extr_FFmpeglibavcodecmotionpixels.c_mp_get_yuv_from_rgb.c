#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  YuvPixel ;
struct TYPE_5__ {TYPE_1__* frame; } ;
struct TYPE_4__ {int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_2__ MotionPixelsContext ;

/* Variables and functions */
 int /*<<< orphan*/ * mp_rgb_yuv_table ; 

__attribute__((used)) static YuvPixel mp_get_yuv_from_rgb(MotionPixelsContext *mp, int x, int y)
{
    int color;

    color = *(uint16_t *)&mp->frame->data[0][y * mp->frame->linesize[0] + x * 2];
    return mp_rgb_yuv_table[color];
}