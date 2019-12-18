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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int w; int h; int motion_x; int motion_y; int motion_scale; int dst_x; int dst_y; int src_x; int src_y; int source; scalar_t__ flags; } ;
typedef  TYPE_1__ AVMotionVector ;

/* Variables and functions */
 scalar_t__ IS_16X8 (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_8X16 (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_8X8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_mb(AVMotionVector *mb, uint32_t mb_type,
                  int dst_x, int dst_y,
                  int motion_x, int motion_y, int motion_scale,
                  int direction)
{
    mb->w = IS_8X8(mb_type) || IS_8X16(mb_type) ? 8 : 16;
    mb->h = IS_8X8(mb_type) || IS_16X8(mb_type) ? 8 : 16;
    mb->motion_x = motion_x;
    mb->motion_y = motion_y;
    mb->motion_scale = motion_scale;
    mb->dst_x = dst_x;
    mb->dst_y = dst_y;
    mb->src_x = dst_x + motion_x / motion_scale;
    mb->src_y = dst_y + motion_y / motion_scale;
    mb->source = direction ? 1 : -1;
    mb->flags = 0; // XXX: does mb_type contain extra information that could be exported here?
    return 1;
}