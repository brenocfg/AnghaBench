#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ video_frame_info_t ;
struct TYPE_8__ {int /*<<< orphan*/  device; } ;
typedef  TYPE_2__ d3d10_video_t ;
struct TYPE_9__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; scalar_t__ top; scalar_t__ left; } ;
typedef  TYPE_3__ D3D10_RECT ;

/* Variables and functions */
 int /*<<< orphan*/  D3D10SetScissorRects (int /*<<< orphan*/ ,int,TYPE_3__*) ; 

__attribute__((used)) static void d3d10_clear_scissor(d3d10_video_t *d3d10, video_frame_info_t *video_info)
{
   D3D10_RECT scissor_rect;

   scissor_rect.left   = 0;
   scissor_rect.top    = 0;
   scissor_rect.right  = video_info->width;
   scissor_rect.bottom = video_info->height;

   D3D10SetScissorRects(d3d10->device, 1, &scissor_rect);
}