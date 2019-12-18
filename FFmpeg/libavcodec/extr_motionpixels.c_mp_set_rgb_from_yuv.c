#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/  u; int /*<<< orphan*/  v; int /*<<< orphan*/  y; } ;
typedef  TYPE_2__ YuvPixel ;
struct TYPE_8__ {TYPE_1__* frame; } ;
struct TYPE_6__ {int* linesize; int /*<<< orphan*/ ** data; } ;
typedef  TYPE_3__ MotionPixelsContext ;

/* Variables and functions */
 int mp_yuv_to_rgb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mp_set_rgb_from_yuv(MotionPixelsContext *mp, int x, int y, const YuvPixel *p)
{
    int color;

    color = mp_yuv_to_rgb(p->y, p->v, p->u, 1);
    *(uint16_t *)&mp->frame->data[0][y * mp->frame->linesize[0] + x * 2] = color;
}